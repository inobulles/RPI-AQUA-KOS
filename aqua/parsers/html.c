
// Entire credit goes to Vlad Ionescu
// Original repository can be found at `https://github.com/inobulles/AquaOSBrowser`
// This file may not be from the latest commit

//#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
//typedef signed long int32_t;
typedef signed long long int64_t;

#define bool uint8_t
#define true 1
#define false 0

typedef struct String String;
typedef struct Property Property;
typedef struct HtmlTag HtmlTag;
typedef struct Node Node;

void mfree(void* pointer, uint32_t bytes);

void mfree(void* pointer, uint32_t bytes) {
  free((void*) pointer);
}


struct Node  {
  void* data;
  Node* next;
  Node* prev;
};

Node* Node_GetNewNode(const void* x);
Node* Node_InsertAfter(Node* node, const void* x);
Node* Node_At(Node* node, int pos);

struct String {
  int* len;
  Node* head;
  Node* tail;
};

String* String_AppendChar(String* string, const char* mChar);
int String_Compare(String* a, String* b);
String* String_ParseStringInStringUntilNonAlpha(String* str);
String* String_ParseStringInStringUntilNonAlphaStartPos(String* str, int startPos);
String* String_ParseStringInStringUntilChar(String* str, const char ch);
String* String_ParseStringInStringUntilCharStartPos(String* str, const char ch, int startPos);

// pos if found, -1 if not found
int String_FindChar(String* str, const char ch);
// pos relative to startPos if found, -1 if not found
int String_FindCharStartPos(String* str, const char ch, int startPos);

struct Property {
  String* propertyName;
  String* propertyValue;
};

struct HtmlTag {
  String* tagName;
  int* propertiesCount;
  Node *headProperties, *tailProperties;
  HtmlTag* parent;
  int* childrenCount;
  Node *headChildren, *tailChildren;
};

bool isalpha(const char ch);
bool isnumber(const char ch);
bool isalnum(const char ch);
String* parseString(const char* pointer);
void parseCss(HtmlTag* tag, String* cssCode);
HtmlTag* parseHtml(const char* myHtmlStr);
void printString(String* str);
void printHtml(HtmlTag *rootTag);


Node* Node_GetNewNode(const void* x) {
  Node* newNode = malloc(sizeof(Node));
  newNode->data = (void*) x;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

Node* Node_InsertAfter(Node* node, const void* x) {
  Node* newNode = Node_GetNewNode(x);
  if(node == NULL) {
    node = newNode;
    return node;
  }
  node->next = newNode;
  newNode->prev = node;
  return newNode;
}

Node* Node_At(Node* node, int pos) {
  Node* newNode = node;
  if(pos < 0) {
    while(pos < 0 && newNode->prev != NULL) {
      newNode = newNode->prev;
      pos++;
    }
    if(pos < 0) {
      return NULL;
    }
  } else {
    while(pos > 0 && newNode->next != NULL) {
      newNode = newNode->next;
      pos--;
    }
    if(pos > 0) {
      return NULL;
    }
  }
  return newNode;
}

String* String_AppendChar(String* string, const char* mChar) {
  if(string == NULL) {
    string = malloc(sizeof(String));
    string->len = malloc(sizeof(int));
    (*string->len) = 0;
    string->head = NULL;
    string->tail = NULL;
  }
  (*string->len)++;
  string->tail = Node_InsertAfter(string->tail, mChar);
  if((*string->len) == 1) {
    string->head = string->tail;
  }
  return string;
}

int String_Compare(String* a, String* b) {
  Node* idxa = a->head;
  Node* idxb = b->head;
  while(idxa != NULL && idxb != NULL) {
    if((*(char*)idxa->data) < (*(char*)idxb->data)) {
      return -1;
    } else if((*(char*)idxa->data) > (*(char*)idxb->data)) {
      return 1;
    }
    idxa = idxa->next;
    idxb = idxb->next;
  }
  if(idxa != NULL && idxb == NULL) {
    return 1;
  } else if(idxa == NULL && idxb != NULL) {
    return -1;
  }
  return 0;
}

String* String_ParseStringInStringUntilNonAlpha(String* str) {
  Node* idx = str->head;
  String* ret = parseString("");
  while(idx != NULL && isalpha(*(char*)idx->data)) {
    ret = String_AppendChar(ret, ((char*)idx->data));
    idx = idx->next;
  }
  return ret;
}

String* String_ParseStringInStringUntilNonAlphaStartPos(String* str, int startPos) {
  Node* idx = str->head;
  String* ret = parseString("");
  while(idx != NULL && startPos > 0) {
    idx = idx->next;
    startPos--;
  }
  while(idx != NULL && isalpha(*(char*)idx->data)) {
    ret = String_AppendChar(ret, ((char*)idx->data));
    idx = idx->next;
  }
  return ret;
}

String* String_ParseStringInStringUntilChar(String* str, const char ch) {
  Node* idx = str->head;
  String* ret = parseString("");
  while(idx != NULL && (*(char*)idx->data) != ch) {
    ret = String_AppendChar(ret, ((char*)idx->data));
    idx = idx->next;
  }
  return ret;
}

String* String_ParseStringInStringUntilCharStartPos(String* str, const char ch, int startPos) {
  Node* idx = str->head;
  String* ret = parseString("");
  while(idx != NULL && startPos > 0) {
    idx = idx->next;
    startPos--;
  }
  while(idx != NULL && (*(char*)idx->data) != ch) {
    ret = String_AppendChar(ret, ((char*)idx->data));
    idx = idx->next;
  }
  return ret;
}

// pos if found, -1 if not found
int String_FindChar(String* str, const char ch) {
  int pos = 0;
  Node* idx = str->head;
  while(idx != NULL) {
    if((*(char*)idx->data) == ch) {
      return pos;
    }
    idx = idx->next;
    pos++;
  }
  return -1;
}

// pos relative to startPos if found, -1 if not found
int String_FindCharStartPos(String* str, const char ch, int startPos) {
  int pos = 0;
  Node* idx = str->head;
  while(idx != NULL && startPos > 0) {
    idx = idx->next;
    startPos--;
  }
  while(idx != NULL) {
    if((*(char*)idx->data) == ch) {
      return pos;
    }
    idx = idx->next;
    pos++;
  }
  return -1;
}

bool isalpha(const char ch) {
  if((ch >= 'A' && ch <= 'Z') ||
      (ch >= 'a' && ch <= 'z')) {
    return true;
  }
  return false;
}

bool isnumber(const char ch) {
  if(ch >= '0' && ch <= '9') {
    return true;
  }
  return false;
}

bool isalnum(const char ch) {
  if(isnumber(ch) ||
      isalpha(ch)) {
    return true;
  }
  return false;
}

String* parseString(const char* pointer) {
  String* myStr = NULL;
  int lim = strlen(pointer);
  int idx = 0;
  while(idx < lim && isalnum(pointer[idx])) {
    myStr = String_AppendChar(myStr, &pointer[idx]);
    idx++;
  }
  return myStr;
}

void parseCss(HtmlTag* tag, String* cssCode) {
  Property *cssProperty = malloc(sizeof(Property));
  int cssCodeStrLen = *cssCode->len;

  for(int myCssCodeStrIdx = 0; myCssCodeStrIdx < cssCodeStrLen; myCssCodeStrIdx++) {
    // Parse css property name
    cssProperty->propertyName = String_ParseStringInStringUntilCharStartPos(cssCode, ':', myCssCodeStrIdx);
    myCssCodeStrIdx += (*cssProperty->propertyName->len) + 1;

    // Skip to css property value
    myCssCodeStrIdx += String_FindCharStartPos(cssCode, ':', myCssCodeStrIdx) + 1;

    // Parse css property value
    cssProperty->propertyValue = String_ParseStringInStringUntilCharStartPos(cssCode, ';', myCssCodeStrIdx);
    myCssCodeStrIdx += (*cssProperty->propertyValue->len) + 1;

    // Skip to end of css property
    myCssCodeStrIdx += String_FindCharStartPos(cssCode, ';', myCssCodeStrIdx);

    // Add the css property to the tag properties array
    (*tag->propertiesCount)++;
    tag->tailProperties = Node_InsertAfter(tag->tailProperties, cssProperty);
    if(tag->headProperties == NULL) {
      tag->headProperties = tag->tailProperties;
    }
  }
}

HtmlTag* parseHtml(const char* myHtmlStr) {
  HtmlTag* root_htmlTag = NULL;
  HtmlTag* prevTag = root_htmlTag;

  int myHtmlStrLen = strlen(myHtmlStr);

  String* styleCss = parseString("style");

  for(int myHtmlStrIdx = 0; myHtmlStrIdx < myHtmlStrLen; myHtmlStrIdx++) {
    if(myHtmlStr[myHtmlStrIdx] == '<' &&
        myHtmlStrIdx + 1 < myHtmlStrLen && myHtmlStr[myHtmlStrIdx + 1] == '/') {
      if(prevTag != NULL) {
        prevTag = prevTag->parent;
      }
    } else if(myHtmlStr[myHtmlStrIdx] == '<') {
      // Create a new tag and initialize its vars
      HtmlTag* new_tag = malloc(sizeof(HtmlTag));
      new_tag->childrenCount = malloc(sizeof(int));
      new_tag->propertiesCount = malloc(sizeof(int));
      (*new_tag->childrenCount) = 0;
      (*new_tag->propertiesCount) = 0;
      new_tag->headChildren = new_tag->tailChildren =
                                new_tag->headProperties =
                                  new_tag->tailProperties = NULL;
      new_tag->parent = prevTag;

      // Parse the tag name
      new_tag->tagName = parseString(myHtmlStr + myHtmlStrIdx + 1);

      // Move the index forward so we continue parsing after the tag name
      myHtmlStrIdx += (*new_tag->tagName->len) + 1;

      Property* property = malloc(sizeof(Property));
      property->propertyName = NULL;
      property->propertyValue = NULL;

      while(myHtmlStrIdx < myHtmlStrLen && myHtmlStr[myHtmlStrIdx] != '>') {
        if(myHtmlStr[myHtmlStrIdx] != ' ') {
          // Parse property name
          property->propertyName = parseString(myHtmlStr + myHtmlStrIdx);
          myHtmlStrIdx += (*property->propertyName->len) + 1;

          // Skip to property value
          while(myHtmlStrIdx < myHtmlStrLen && myHtmlStr[myHtmlStrIdx] != '"') {
            myHtmlStrIdx++;
          }
          myHtmlStrIdx++;

          // Parse property value
          property->propertyValue = parseString("");
          while(myHtmlStrIdx < myHtmlStrLen && myHtmlStr[myHtmlStrIdx] != '"') {
            property->propertyValue = String_AppendChar(property->propertyValue, myHtmlStr + myHtmlStrIdx);
            myHtmlStrIdx++;
          }

          if(String_Compare(property->propertyName, styleCss) == 0) {
            // Parse all css properties
            parseCss(new_tag, property->propertyValue);
          } else {
            // Add the property to the properties array of the tag
            (*new_tag->propertiesCount)++;
            new_tag->tailProperties = Node_InsertAfter(new_tag->tailProperties, property);
            if(new_tag->headProperties == NULL) {
              new_tag->headProperties = new_tag->tailProperties;
            }
          }
          
        }
        myHtmlStrIdx++;
      }

      // Add the tag in the hierarchy
      if(prevTag == NULL) {
        root_htmlTag = new_tag;
        prevTag = new_tag;
      } else {
        (*prevTag->childrenCount)++;
        prevTag->tailChildren = Node_InsertAfter(prevTag->tailChildren, new_tag);
        if(prevTag->headChildren == NULL) {
          prevTag->headChildren = prevTag->tailChildren;
        }
        prevTag = new_tag;
      }
    }
  }
  return root_htmlTag;
}

void printString(String* str){
  Node* idx = str->head;
  int i = 0;
  
  while (idx!=NULL){
    printf("%c",*(char*)idx->data);
    idx=idx->next;
  }
}

void printHtml(HtmlTag *rootTag) {
  Node* childrenIdxStackTail = NULL;
  Node* tagsStackTail = NULL;

  printString(rootTag->tagName);
  printf("\n");

  // Add root tag to tags stack
  tagsStackTail = Node_InsertAfter(tagsStackTail, rootTag);
  childrenIdxStackTail = Node_InsertAfter(childrenIdxStackTail, malloc(sizeof(int)));
  *(int*)childrenIdxStackTail->data=0;

  int lvl = 1;

  while(tagsStackTail != NULL) {
    if (*(int*)childrenIdxStackTail->data < *((HtmlTag*)tagsStackTail->data)->childrenCount){
      HtmlTag* child = (HtmlTag*)(Node_At(((HtmlTag*)tagsStackTail->data)->headChildren, *(int*)childrenIdxStackTail->data)->data);
      (*(int*)childrenIdxStackTail->data)++;

      // Print child name
      for (int lvlIdx=0;lvlIdx<lvl;lvlIdx++){
        printf("    ");
      }
      printString(child->tagName);
      printf(" (");
      
      Node* current_property_node;
      Property* current_property;
      
      if (*child->propertiesCount) {
		  current_property_node = child->headProperties;
		current_property = current_property_node->data;
		
	}
      
      int i;
      for (i = 0; i < *child->propertiesCount; i++) {
		  printString(current_property->propertyName);
		  printf(" is ");
		  printString(current_property->propertyValue);
		  
		  if (i < *child->propertiesCount - 1) {
			  printf(", ");
			  current_property_node = child->headProperties->next;
			current_property = current_property_node->data;
			
		}
		  
	  }
      
      printf(")\n");

      // Add child tag to tags stack
      tagsStackTail=Node_InsertAfter(tagsStackTail,child);
      childrenIdxStackTail = Node_InsertAfter(childrenIdxStackTail,malloc(sizeof(int)));
      *(int*)childrenIdxStackTail->data=0;
      lvl++;
      continue;
    }
    lvl--;
    for (int lvlIdx=0;lvlIdx<lvl;lvlIdx++){
      printf("    ");
    }
    printf("END ");
    printString(((HtmlTag*)tagsStackTail->data)->tagName);
    printf("\n");
    tagsStackTail=(tagsStackTail->prev);
    childrenIdxStackTail=(childrenIdxStackTail->prev);
    if (childrenIdxStackTail!=NULL){
      mfree(childrenIdxStackTail->next,sizeof(int));
      childrenIdxStackTail->next=NULL;
    }
  }
}

int main() {
  const char* html = "<html>\
					<head>\
						<title>This is a test</title>\
						\
					</head>\
					\
					<body>\
						<div style=\"background-color:#FF00FF;\">\
							<h1 font=\"monospace\">Hello world!</h1>\
							This is just some normal text.\
							<center>... and this is some centered text :)</center>\
						</div>\
						\
					</body>\
					\
				</html>";
  // PARSE AND REPENT YOU PEASANT
  HtmlTag* iAmGroot = parseHtml(html);
  // sho me da wae
  printHtml(iAmGroot);
  return 0; // gg wp
}
