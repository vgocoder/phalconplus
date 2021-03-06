namespace PhalconPlus\Base;

class ProtoBuffer implements \JsonSerializable
{
    public function softClone(array data)
    {
        var key, val;
        for key, val in data {
            if property_exists(this, key) {
                // error_log("SoftClone: ". key . ": " . var_export(val, true));
                this->__set(key, val);
            }
        }
    }

    public function __set(string! key, val)
    {
        var method, param, paramClass, paramClassRef, paramObj;
        let method = "set" . key->upperfirst();
        // error_log("Proto__set: " . key . ": " . var_export(val, true));
        if method_exists(this, method) {
            let param = new \ReflectionParameter([this, method], 0);
            if param->getClass() {
                // error_log("Proto__set: param class" . param->getClass());
                // error_log("Proto__set: value" . var_export(val, true));
                let paramClass = param->getClass()->getName();
                let paramClassRef = new \ReflectionClass(paramClass);
                // if is-a ProtoBuffer class
                if paramClassRef->isSubclassOf("\\PhalconPlus\\Base\\ProtoBuffer") {
                    let paramObj = paramClassRef->newInstance();
                    paramObj->softClone(val);
                    let val = paramObj;
                } else {
                    let paramObj = paramClassRef->newInstance(val);
                    let val = paramObj;
                }
            }
            return this->{method}(val);
        }

        // rule break: hard code
        if is_scalar(val) || is_null(val) || is_array(val) {
            let this->{key} = val;
            return this;
        } elseif is_object(val) && val instanceof "\PhalconPlus\Base\ProtoBuffer" {
            let this->{key} = val;
            return this;
        } else {
            throw new \Exception("Please add " . method . " in your class, complex-type vars are not allowed to assign directly");
        }
    }

    public function __isset(string! key)
    {
        if property_exists(this, key) {
            return true;
        }
        return false;
    }

    public function __get(string! key)
    {
        var method;
        let method = "get" . key->upperfirst();

        if method_exists(this, method) {
            return this->{method}();
        }

        if property_exists(this, key) {
            return this->{key};
        }

        return null;
    }

    protected function getSelfVars() -> array
    {
        var objReflection = null;
        var vars = [], pros = [], pro = null;

        let objReflection = new \ReflectionObject(this);
        let pros = objReflection->getProperties();

        for pro in pros {
            pro->setAccessible(true);
            let vars[pro->getName()] = pro->getValue(this);
        }
        return vars;
    }

    public function jsonSerialize()
    {
        return this->toArray();
    }

    public function toArray(bool isArray = false, array data = [])
    {
        var pros = [], newPros = [];

        if isArray == false {
            let pros = this->getSelfVars();
        } else {
            let pros = data;
        }

        var key, val;

        for key, val in pros {
            if is_array(val) {
                let newPros[key] = this->toArray(true, val);
            } elseif is_object(val) && method_exists(val, "toArray") {
                let newPros[key] = val->toArray();
            } elseif is_object(val) && method_exists(val, "__toString") {
                let newPros[key] = val->__toString();
            } else {
                let newPros[key] = val;
            }
        }

        return newPros;

        /* Zephir 暂时不支持 引用传递
        array_walk_recursive(pros, function(&property, key){
            if is_object(property) {
                let property = property->toArray();
            }
        });
        return pros;
        */
    }
}
