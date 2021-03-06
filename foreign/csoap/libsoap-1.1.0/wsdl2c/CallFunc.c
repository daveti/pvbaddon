/** Generated by xsd2c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CallFunc.h"


struct CallFunc* CallFunc_Create()
{
	struct CallFunc* _res;
	_res = (struct CallFunc*)malloc(sizeof(struct CallFunc));

	_res->name = NULL;
	_res->in_head = NULL;
	_res->in_tail = NULL;
	_res->out = NULL;

	return _res;
}

void CallFunc_Free(struct CallFunc* obj)
{
	struct CallVar_List* in_cur;
	struct CallVar_List* in_tmp;
	if (obj == NULL) return;
	if (obj->name != NULL) 
	{
		free(obj->name);
		obj->name = NULL;
	}

	in_cur = obj->in_head;
	while (in_cur != NULL)
	{
		in_tmp = in_cur->next;
		free(in_cur);
		in_cur = in_tmp;
	}
	free(obj);
}

void CallFunc_Sax_Serialize(struct CallFunc* obj,
		 const char *root_element_name,
		 void (*OnStartElement)(const char* element_name, int attr_count, char **keys, char **values, void* userData),
		 void (*OnCharacters)(const char* element_name, const char* chars, void* userData),
		 void (*OnEndElement)(const char* element_name, void* userData),
		 void* userData)
{
	int attrCount, curCount;
	char **keys;
	char **values;
	char buffer[255];

	struct CallVar_List* in_cur;

	attrCount = 0;

	keys = (char**)malloc(sizeof(char*)*attrCount);
	values = (char**)malloc(sizeof(char*)*attrCount);

	curCount = 0;


	OnStartElement(root_element_name, attrCount, keys, values, userData);

	OnStartElement("name", 0, NULL, NULL, userData);
	if (obj->name != NULL)
		OnCharacters("name", obj->name, userData);
	OnEndElement("name", userData);
	in_cur = obj->in_head;
	while (in_cur != NULL)
	{
	if (in_cur->value)
		CallVar_Sax_Serialize(in_cur->value, "in", OnStartElement, OnCharacters, OnEndElement, userData);

		in_cur = in_cur->next;
	}
	if (obj->out)
	CallVar_Sax_Serialize(obj->out, "out", OnStartElement, OnCharacters, OnEndElement, userData);

	OnEndElement(root_element_name, userData);
}

#ifndef _DESERIALIZER_DISABLED_

struct CallFunc* CallFunc_Deserialize(xmlNodePtr xmlRoot)
{
	xmlNodePtr cur;
	xmlChar *key;
	struct CallFunc* obj;
	obj = CallFunc_Create();
	cur = xmlRoot->xmlChildrenNode;
	while (cur != NULL) {
		if (cur->type != XML_ELEMENT_NODE) {
			cur = cur->next;
			continue;
		}
		printf("CallFunc->%s\n", cur->name);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"name"))){
			key = xmlNodeListGetString(cur->doc, cur->xmlChildrenNode, 1);
			CallFunc_Set_name(obj, (const char*)key);
			/*xmlFree(key);*/
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"in"))){
			CallFunc_Add_in( obj, CallVar_Deserialize(cur) );
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"out"))){
			CallFunc_Set_out( obj, CallVar_Deserialize(cur) );
		}
	// TODO: 
		cur = cur->next;
	}
	return obj;
}

#endif
char* CallFunc_Get_name(struct CallFunc* obj)
{
	return obj->name;
}

struct CallVar_List* CallFunc_Get_in(struct CallFunc* obj)
{
	return obj->in_head;
}

struct CallVar* CallFunc_Get_out(struct CallFunc* obj)
{
	return obj->out;
}

void CallFunc_Set_name(struct CallFunc* obj, const char* name)
{
	if (obj->name != NULL) free(obj->name);
	obj->name = (char*)malloc(strlen(name)+1);
	strcpy(obj->name, name);
}

void CallFunc_Set_out(struct CallFunc* obj, struct CallVar* out)
{
	obj->out = out;
}

void CallFunc_Add_in(struct CallFunc* obj, struct CallVar* in)
{
	struct CallVar_List* in_node;
	in_node = (struct CallVar_List*)malloc(sizeof(struct CallVar_List));
	in_node->value = in;
	in_node->next = NULL;
	if (obj->in_tail)
	{
		obj->in_tail->next = in_node;
	}
	if (obj->in_head == NULL)
	{
		obj->in_head = in_node;
	}
	obj->in_tail = in_node;
}

