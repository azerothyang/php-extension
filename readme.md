### Zend Macros
```
Z_TYPE_P(*zval) //zval type 

Z_TYPE_PP(**zval) //zval type 

Z_LVAL_P(*zval) //zval long value
Z_LVAL_PP(**zval) //zval long value
Z_STRLEN_P(*zval)

RETVAL_NULL() //set return_value null, but not return control to the calling scope
RETVAL_BOOL(bval)
RETVAL_TRUE
RETVAL_FALSE
RETVAL_LONG(lval)
RETVAL_DOUBLE(dval)
RETVAL_STRING(str, dup)
RETVAL_STRINGL(str,len,dup)
RETVAL_RESOURCE(rval)

ZVAL_NULL(*zval return_value) //set return_value null
ZVAL_BOOL(*zval return_value, bval) 
ZVAL_TRUE(*zval return_value) 
ZVAL_FALSE(*zval return_value) 
ZVAL_LONG(*zval return_value, lval) 
ZVAL_DOUBLE(*zval return_value, dval) 
ZVAL_STRING(*zval return_value, str, dup) 
ZVAL_STRINGL(*zval return_value, str, len, dup)
ZVAL_RESOURCE(*zval return_value, rval) 

#define RETURN_RESOURCE(l)              { RETVAL_RESOURCE(l); return; } //set return_value and return immediately
#define RETURN_BOOL(b)                  { RETVAL_BOOL(b); return; }
#define RETURN_NULL()                   { RETVAL_NULL(); return;}
#define RETURN_LONG(l)                  { RETVAL_LONG(l); return; }
#define RETURN_DOUBLE(d)                { RETVAL_DOUBLE(d); return; }
#define RETURN_STRING(s, duplicate)     { RETVAL_STRING(s, duplicate); return; }
#define RETURN_STRINGL(s, l, duplicate) { RETVAL_STRINGL(s, l, duplicate); return; }
#define RETURN_EMPTY_STRING()           { RETVAL_EMPTY_STRING(); return; }
#define RETURN_ZVAL(zv, copy, dtor)     { RETVAL_ZVAL(zv, copy, dtor); return; }
#define RETURN_FALSE                    { RETVAL_FALSE; return; }
#define RETURN_TRUE						{ RETVAL_TRUE; return; }
```

###php_printf
```
long foo=88;
php_printf("The integer value of the parameter you passed is: %ld\n", foo);
```

###zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len)
```
first-arg:
	an int representing the number of arguments actually
	passed to the function

second-arg:
	b Boolean; zend_bool
	l Integer; long
	d Floating point; double
	s String char*; int
	r Resource; zval*
	a Array; zval*
	o Object instance; zval*
	O Object instance of a specified type; zval*, zend_class_entry*
	z Non-specific zval; zval*
	Z Dereferenced non-specific zval; zval**

example:
	long foo;
		if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &foo) == FAILURE) {
			RETURN_NULL();
		}
		php_printf("The integer value of the parameter you passed is: %ld\n", foo);
		RETURN_TRUE;
```

### https://blog.csdn.net/treesky/article/details/46432541