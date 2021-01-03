/* phpgenerator.c
 *
 * This file provides functions to generate PHP classes in the form of strings
 */
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

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
	struct php_method methods[PHP_METHODS_MAX];
	struct php_member members[PHP_MEMBERS_MAX];
	int number_methods;
	int number_members;
};

struct json_object {
	int id;
	struct json_object *first, *second;
};


/**
 * Generates a string containing a full synthax-complient, PHP class
 */
char* generate_php_class(struct php_class* php_class, char result[300]) {
	strcat(result, "class ");
	strcat(result, php_class->name);
	strcat(result, "\n{");
	
	for(int i = 0; i < php_class->number_methods; i++) {
		strcat(result,"function ");
		strcat(result, php_class->methods[i].name);
		strcat(result, "\n{\n}\n");
	}	

	for(int i = 0; i < php_class->number_members; i++) {
		strcat(result, "$");
		strcat(result, php_class->members[i].name);
		strcat(result, ";\n");
	}

	strcat(result, "\n}\n");
	
	return result;
}

/**
 * Generates php_class objects from a JSON string, and return the number of php classes
 */
int map_json_to_php_classes(char json[MAX_JSON_CHARACTERS], size_t size_json, struct php_class* php_classes) {
	int number_of_classes = 0;
	int php_object_index = 0;
	bool bracket_opened = 0;
	bool braces_opened = 0;
	int j = 0;
	char classname[PHP_NAME_MAX_LENGTH];

	for(int i = 0; i < strlen(json); i++){
		if(json[i] == '{') {
			if(braces_opened == 1){
				return 0; //Nested objects not supported
			}
			braces_opened = 1;
			if(php_object_index != 0) {
				php_object_index += 1;
			}
		} else if (json[i] == '}') {
			if(braces_opened == 0){
				return 0; //Nested objects not supported
			}
			braces_opened = 0;
		} else if (json[i] == ':') {
			if (braces_opened = 0) {
				return 0; //Bad JSON formating
			}
		} else if (json[i] == '[') {
			if(bracket_opened == 1) {
				return 0; //Nested arrays not supported
			}
			bracket_opened = 1;
		} else if (json[i] == ']') {
			if(bracket_opened == 0) {
				return 0; //Nested arrays not supported
			}
			bracket_opened = 0;
		} else if (json[i] == 'c' && json[i+1] == 'l' && json[i+2] == 'a' && json[i+3] == 's' && json[i+4] == 's') { //class name
		
			if(json[i+5] == ':'){
				j = i + 6;
			} else if (json[i+6] == ':') {
				j = i + 7;
			} else {
				continue;
			}	

			//Writes the classname
			while(j < strlen(json) && json[j] != EOF &&  json[j] != '\n' && json[j] != '}') {
				if(json[j] != ' '){
					strncat(classname, &json[j], 1);
				}

				j = j + 1;
			}

			number_of_classes = number_of_classes + 1;
			i = j - 1;
			strcpy(php_classes[php_object_index].name, classname);
		}

	}	

	return number_of_classes;
}


/*
 *This functions converts a JSON string into a string of PHP classes
 */
char* jsontophp(char json[MAX_JSON_CHARACTERS], char conversion_result[1000]) {
	
	struct php_class php_classes[1000];
	int number_of_classes;
	char php_class_string[300];
	size_t size_json = strlen(json);

	if(size_json > MAX_JSON_CHARACTERS) {
		sprintf(conversion_result, "JSON input is too long, max number of characters is %d", MAX_JSON_CHARACTERS);
		return conversion_result;
	}
	
	number_of_classes = map_json_to_php_classes(json, size_json, php_classes);

	for(int i = 0; i < number_of_classes; i++) {
		strcat(conversion_result, generate_php_class(&php_classes[i], php_class_string));
	}

	return conversion_result;
}
