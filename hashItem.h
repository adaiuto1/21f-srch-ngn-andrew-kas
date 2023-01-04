#ifndef INC_21F_FINAL_PROJ_TEMPLATE_HASHITEM_H
#define INC_21F_FINAL_PROJ_TEMPLATE_HASHITEM_H
struct hashItem{
    char* key;
    string value;
    hashItem(char*, string&);
};
hashItem::hashItem(char* sk, string& sv){
    key = sk;
    value = sv;
}
#endif //INC_21F_FINAL_PROJ_TEMPLATE_HASHITEM_H
