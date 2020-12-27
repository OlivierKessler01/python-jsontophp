/* phpgenerator.c
 *
 * This file provides functions to generate php classes
 *
 *
 */

/*
 *This functions converts JSON Objects into PHP objects
 */
void jsontophp(char *json, size_t size_json, char *conversion_result) {
    conversion_result = (char*)malloc(sizeof(char)*size_json);

    for(int i=0; i < size_json; i++)
    {
        conversion_result[i] = json[i];
        printf("%s", json);
    }
}

