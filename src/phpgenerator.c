/* phpgenerator.c
 *
 * This file provides functions to generate PHP classes in the form of strings
 */

#define MAX_JSON_NESTING 30
#define PHP_NAME_MAX_LENGTH 20
#define PHP_METHODS_MAX 30
#define MAX_JSON_CHARACTERS 1000
#define PHP_MEMBERS_MAX 30

struct php_method {
	char name[PHP_NAME_MAX_LENGTH];
};

struct php_member {
	char name[PHP_NAME_MAX_LENGTH];
};

struct php_class {
	char name[PHP_NAME_MAX_LENGTH];
	php_method methods[PHP_METHODS_MAX];
	php_member members[PHP_MEMBERS_MAX];
	int number_methods;
	int number_members;
};

struct json_object {
	int id;
	json_object children[MAX_JSON_NESTING];
};


/**
 * Generates a string containing a full synthax-complient, PHP class
 */
char* generate_php_class(php_class* php_class) {
	char result[300] = "class ";
	strcat(result, php_class->name);
	strcat(result, " {");
	
	for(int i = 0; i < php_class->number_methods; i++) {
		strcat(result,"function ");
		strcat(result, php_class->methods[i]->name);
		strcat(result, " {}\n");
	}	

	for(int i = 0; i < php_class->number_members; i++) {
		strcat(result, "$");
		strcat(result, php_class->members[i]->name);
		strcar(result, ";\n");
	}

	strcat(result, "}\n");
	
	return result;
}

/**
 * Generates php_class objects from a JSON string, and return the number of php classes
 */
int map_json_to_php_classes(char *json, size_t size_json, php_class* php_classes) {
	int number_of_classes = 0;
	int php_object_index = 0;
	bool bracket_opened = 0;
	bool braces_opened = 0;
	char classname[PHP_NAME_MAX_LENGTH] = "";

	for(int i = 0; i < size_json, i++){
		if(json[i] == "{") {
			braces_opened = 1;
			php_object_index += 1;
			php_classes[php_object_index] = {}
		} else if (json[i] == "}") {
			braces_opened = 0;
		} else if (json[i] == ":") {
			if (braces_opened = 0) {
				return 0; //Bad JSON formating
			}
		} else if (json[i] == "[") {
			if(bracked_opened == 1) {
				return 0; //Nested arrays not supported
			}
			bracket_opened = 1;
		} else if (json[i] == "]") {
			if(bracket_opened == 0) {
				return 0; //Nested arrays not supported
			}
			bracket_opened = 0;
		} else if (json[i] == "c" && json[i+1] == "l" && json[i+2] == "a"
				&& json[i+3] == "s" && json[i+4] == "s" && (json[i+5] == ":" || json[i+6] = ":")) { //class name
			
			
			while( json[j] != "\n") {
				strcat(classname, json[j]);
			}

			php_classes[php_object_index]->name = classname;
		}

	}	

	return number_of_classes;
}


/*
 *This functions converts a JSON string into a string of PHP classes
 */
char* jsontophp(char *json, size_t size_json, char *conversion_result) {
	char result_string[1000] = "";
	php_class* php_classes[1000];
	int number_of_classes;

	if(size_json > 1000) {
		result_string = sprintf("JSON input is too long, max number of characters is %d", MAX_JSON_CHARACTERS);
		return result_string;
	}
	
	number_of_classes = map_json_to_php_objects(json, size_json, php_objects);
	
	for(int i = 0; i < number_of_classes; i++) {
		strcat(result_string, generate_php_class(php_objects[i]));
	}

	return result_string;
}

