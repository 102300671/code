#include <iostream>
#define ElemType int
#define MAXSIZE 100
#define OK 1
#define ERROR 0
using namespace std;
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SqList;
int InitList(SqList &L)
{
    L.length = 0;
    return OK;
}
int ListInsert(SqList &L, int i, ElemType e)
{
    if (i < 1 || i > L.length + 1)
        return ERROR;
    if (L.length >= MAXSIZE)
        return ERROR;
    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;
    L.length++;
    return OK;
}
int ListDelete(SqList &L, int i, ElemType &e)
{
    if (i < 1 || i > L.length)
        return ERROR;
    e = L.data[i - 1];
    for (int j = i; j < L.length; j++)
        L.data[j - 1] = L.data[j];
    L.length--;
    return OK;
}
int GetElem(SqList L, int i, ElemType &e)
{
    if (i < 1 || i > L.length)
        return ERROR;
    e = L.data[i - 1];
    return OK;
}
int LocateElem(SqList L, ElemType e)
{
    for (int i = 0; i < L.length; i++)
        if (L.data[i] == e)
            return i + 1;
    return 0;
}
int main() {
    SqList L;
    InitList(L);
    while 1 {
        cout << "1.插入元素" << endl;
        cout << "2.删除元素" << endl;
        cout << "3.查找元素" << endl;
        cout << "4.查找位置" << endl;
        cout << "5.退出" << endl;
        int op;
        cin >> op;
        if (op == 1) {
            cout << "请输入插入位置和元素值" << endl;
            int i, e;
            cin >> i >> e;
            ListInsert(L, i, e);
        } else if (op == 2) {
            cout << "请输入删除位置" << endl;
            int i, e;
            cin >> i;
            ListDelete(L, i, e);
            cout << "删除元素为" << e << endl;
        } else if (op == 3) {
            cout << "请输入查找位置" << endl;
            int i, e;
            cin >> i;
            GetElem(L, i, e);
            cout << "查找元素为" << e << endl;
        } else if (op == 4) {
            cout << "请输入查找元素" << endl;
            int e;
            cin >> e;
            int i = LocateElem(L, e);
            cout << "查找位置为" << i << endl;
        } else if (op == 5) {
            break;
        }
    }
}