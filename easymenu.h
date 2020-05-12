#define MAX_LIST_ITEM 10
#define MAX_MENU_ITEM 10
#define MAX_DEPTH 4

byte downArrowChar[] = {0x00, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04, 0x00};
byte upArrowChar[] = {0x00, 0x04, 0x0E, 0x1F, 0x04, 0x04, 0x04, 0x00};
byte rightArowChar[] = {0x00, 0x00, 0x04, 0x06, 0x1F, 0x06, 0x04, 0x00};
byte leftArrowChar[] = {0x00, 0x00, 0x04, 0x0C, 0x1F, 0x0C, 0x04, 0x00};
byte returnArrowChar[] = {0x00, 0x01, 0x01, 0x05, 0x0D, 0x1F, 0x0C, 0x04};

class easyMenu{

};


struct itemValue{
    char *label;
    int value;
};

enum entryType{MENU,BOOL,LIST,INT,FLOAT};

struct menuItem{
    char *label;
    entryType entryType;
    void *paramPointer;
};

class myParam{
  
}

class boolParam{
    public:
        char* label;
        bool* target;
        char* trueName;
        char* falseName;
        boolParam(char* label, bool* target, char* trueName="YES", char* falseName="NO"):
            label(label),
            target(target),
            trueName(trueName),
            falseName(falseName) {}
        char* changeItem(int clicks){
            
        }
};


class intParam{
    public:
        char* label;
        int* target;
        int minValue;
        int maxValue;
        int stepValue;
        intParam(char* label, int* target, int minValue=0, int maxValue=10, int stepValue=1):
            label(label),
            target(target),
            minValue(minValue),
            maxValue(maxValue),
            stepValue(stepValue){}
};

class doubleParam{
    public:
        char *label;
        double *target;
        double minValue;
        double maxValue;
        double stepValue;
        doubleParam(char* label, double* target, double minValue=0, double maxValue=2.5, int stepValue=0.1):
            label(label),
            target(target),
            minValue(minValue),
            maxValue(maxValue),
            stepValue(stepValue){}
};

class listParam{
    public:
        char* label;
        int* target;
        itemValue list[];
        unsigned int totalItems;
        listParam(char* label, int* target, )
};


struct menuList{
    menuItem list[MAX_MENU_ITEM];
    uint8_t entryCount;
};


bool p1;

menuList topMenu={
    {"Bool1", BOOL,&boolParam("BLabel1",&p1,"SI","NO")}

}
