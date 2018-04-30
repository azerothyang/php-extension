### zval type
```
typedef struct _zval_struct {
	zvalue_value value;
	zend_uint refcount;
	zend_uchar type;
	zend_uchar is_ref;
} zval;

typedef union _zvalue_value {
	long lval;
	double dval;
	struct {
	char *val;
	int len;
	} str;
	HashTable *ht;
	zend_object_value obj;
} zvalue_value;


IS_NULL
IS_BOOL
IS_LONG
IS_DOUBLE
IS_STRING
IS_ARRAY
IS_OBJECT
IS_RESOURCE
```


### Zend Macros
```
Z_TYPE_P(zval*) //zval type 

Z_TYPE_PP(zval**) //zval type 
MAKE_STD_ZVAL(zval*) //这个宏会用内核的方式来申请一块内存并将其地址付给pzv，并初始化它的refcount和is_ref连个属性，更棒的是，它不但会自动的处理内存不足问题，还会在内存中选个最优的位置来申请。
Z_LVAL_P(zval*) //zval long value
Z_LVAL_PP(zval**) //zval long value
Z_STRLEN_P(zval*)


//zend_string init
zend_string* zend_string_init(char *, int strLen, 0);
zend_string_release(zend_string *);

zend_string* zval_get_string(zval*);
struct _zend_string {
    zend_refcounted_h gc; /*gc信息*/
    zend_ulong        h;  /* hash value */
    size_t            len; /*字符串长度*/
    char              val[1]; /*字符串起始地址*/
};
#define ZSTR_VAL(zstr)  (zstr)->val
#define ZSTR_LEN(zstr)  (zstr)->len
#define ZSTR_H(zstr)    (zstr)->h
#define ZSTR_HASH(zstr) zend_string_hash_val(zstr)



RETVAL_NULL() //set return_value null, but not return control to the calling scope
RETVAL_BOOL(bval)
RETVAL_TRUE
RETVAL_FALSE
RETVAL_LONG(lval)
RETVAL_DOUBLE(dval)
RETVAL_STRING(str, dup)
RETVAL_STRINGL(str,len,dup)
RETVAL_RESOURCE(rval)

ZVAL_NULL(zval* return_value) //set return_value null
ZVAL_BOOL(zval* return_value, bval) 
ZVAL_TRUE(zval* return_value) 
ZVAL_FALSE(zval* return_value) 
ZVAL_LONG(zval* return_value, lval) 
ZVAL_DOUBLE(zval* return_value, dval) 
ZVAL_STRING(zval* return_value, str, dup) 
ZVAL_STRINGL(zval* return_value, str, len, dup)
ZVAL_RESOURCE(zval* return_value, rval) 

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

### php_printf
```
long foo=88;
php_printf("The integer value of the parameter you passed is: %ld\n", foo);
```

###	PHPWRITE(char* name, int name_len)


### Zend Hash API
```
int zend_hash_init(HashTable *ht, uint nSize, hash_func_t pHashFunction,
dtor_func_t pDestructor, zend_bool persistent)
int zend_hash_add(HashTable *ht, char *arKey, uint nKeyLen, void **pData, uint nDataSize, void *pDest);
int zend_hash_update(HashTable *ht, char *arKey, uint nKeyLen, void *pData, uint nDataSize, void **pDest);
int zend_hash_index_update(HashTable *ht, ulong h, void *pData, uint nDataSize, void **pDest);
int zend_hash_next_index_insert(HashTable *ht, void *pData, uint nDataSize, void **pDest);
ulong nextid = zend_hash_next_free_element(HashTable *ht);

//they return 1 to indicate that the requested key/index exists or 0 to indicate absence
int zend_hash_exists(HashTable *ht, char *arKey, uint nKeyLen);
int zend_hash_index_exists(HashTable *ht, ulong h);

//they return SUCCESS to indicate that the requested key/index exists or FAILURE to indicate FAIL
zval* ZEND_FASTCALL zend_hash_find(const HashTable *ht, zend_string *key)
int zend_hash_index_find(HashTable *ht, ulong h, void **pData);

examples:
{
	HashTable *ht, 
	sample_data *data1;
	sample_data *data2;
	ulong targetID = zend_hash_next_free_element(ht);
	if (zend_hash_index_update(ht, targetID,
		data1, sizeof(sample_data), NULL) == FAILURE) {
		/* Should never happen */
		return;
	}
	if(zend_hash_index_find(ht, targetID, (void **)&data2) == FAILURE) {
		/* Very unlikely since we just added this element */
		return;
	}

}

//Quick Population and Recall
ulong zend_get_hash_value(char *arKey, uint nKeyLen); //get hashval
int zend_hash_quick_add(HashTable *ht, char *arKey, uint nKeyLen, ulong hashval, void *pData, uint nDataSize, void **pDest);
int zend_hash_quick_update(HashTable *ht, char *arKey, uint nKeyLen, ulong hashval,
void *pData, uint nDataSize, void **pDest);
int zend_hash_quick_find(HashTable *ht, char *arKey, uint nKeyLen, ulong hashval, void **pData);
int zend_hash_quick_exists(HashTable *ht, char *arKey, uint nKeyLen, ulong hashval);

```


### Array Api
```
array_init(zval *arrval)
add_assoc_null(zval *aval, char *key);
add_assoc_bool(zval *aval, char *key, zend_bool bval);
add_assoc_long(zval *aval, char *key, long lval);
add_assoc_double(zval *aval, char *key, double dval);
add_assoc_string(zval *aval, char *key, char *strval, int dup);
add_assoc_stringl(zval *aval, char *key,
char *strval, uint strlen, int dup);
add_assoc_zval(zval *aval, char *key, zval *value);
add_next_index_long(zval*, long);
add_index_zval(zval *zval, ulong index, zval *value);
```


### zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len)

#### Type Modifier 		Meaning
'|' 				Optional parameters follow. When this is specified, all
					previous parameters are considered required and all
					subsequent parameters are considered optional.

'!' 				If a NULL is passed for the parameter corresponding to the
					preceding argument specifier, the internal variable provided
					will be set to an actual NULL pointer as opposed to an IS_NULL zval.

'/' 				If the parameter corresponding to the preceding argument
					specifier is in a copy-on-write reference set, it will be
					automatically separated into a new zval with is_ref==0, and
					refcount==1.

```
first-arg:
	an int representing the number of arguments actually
	passed to the function

second-arg:
	b Boolean; zend_bool
	l Integer; long
	d Floating point; double
	s String ;char*, int
	r Resource; zval*
	a Array; zval*
	o Object instance; zval*
	O Object instance of a specified type; zval*, zend_class_entry*
	z Non-specific zval; zval*
	Z Dereferenced non-specific zval; zval**

example:
	long type parameter:
	{
		long foo;
			if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &foo) == FAILURE) {
				RETURN_NULL();
			}
			php_printf("The integer value of the parameter you passed is: %ld\n", foo);
			RETURN_TRUE;
	}
	char 
	{
		char *name;
		int name_len;
		if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &name, &name_len) == FAILURE) {
			RETURN_NULL();
		}
		php_printf("Hello ");
		PHPWRITE(name, name_len);
		php_printf("!\n");
	}
	serveral parameters
	{
		char *name;
		int name_len;
		char *greeting;
		int greeting_len;
		if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &name, &name_len, &greeting, &greeting_len) == FAILURE) {
			RETURN_NULL();
		}
		php_printf("Hello ");
		PHPWRITE(greeting, greeting_len);
		php_printf(" ");
		PHPWRITE(name, name_len);
		php_printf("!\n");
	}
	
	Optional Parameters
	{
		char *name;
		int name_len;
		char *greeting = "Mr./Mrs.";
		int greeting_len = sizeof("Mr./Mrs.") - 1;
		if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|s", &name, &name_len, &greeting, &greeting_len) == FAILURE) {
			RETURN_NULL();
		}
		php_printf("Hello ");
		PHPWRITE(greeting, greeting_len);
		php_printf(" ");
		PHPWRITE(name, name_len);
		php_printf("!\n");
	}


	
```

### https://blog.csdn.net/treesky/article/details/46432541