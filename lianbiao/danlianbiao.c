//
//  main.c
//  lianbiao
//
//  Created by jia jia  on 2019/8/16.
//  Copyright © 2019年 jia jia . All rights reserved.
//来实现一个链式存储的线性表

#include <stdio.h>
#include <stdlib.h>
#define ERROR -1;
#define OK 1;

//定义一个结点
typedef char ElemType;
typedef int Status;
typedef struct Node //结点类型定义
{
    ElemType data ;
    struct Node  *next ;
}Node,*LinkList ; // linklist 是结构指针类型

//结点在存储使用上更灵活，所以要有释放操作，同时也不用再给表一个空间定值了
//将用到malloc(),realloc(),sizeof(),free() 头文件 #include <stdlib.h>

/*
 malloc(n*sizeof(int)) //申请空间，返回首地址
 realloc(p,sizeof(int)*n) //给p重分配空间
 
 p=(Node*)malloc(sizeof(Node))//强制类转换，给空间类型，把地址给p
 free(p); 动态释放，回收给p分配的内存
 
 */

//单链表1 初始化 因为它的链接方式才叫单链表的，不是因为结点个数
//关于命名： 链接方式分 单链表、循环链表和双链表。
//。       实现角度分 动态链表和静态链表

Status Init_LinkList(LinkList *L) // L 接受指针变量的地址，二级指针可以方便的修改一级指针的值，因为之前定义的LinkList本来返回的就是一个地址，这里*L就是指向地址的指针，指谁改谁
{
    *L = (LinkList)malloc(sizeof(Node)); // 申请空间
    if(!(*L)) return ERROR;
    (*L)->next=NULL;  // 无后继前驱，头节点
    return OK;
}

// 单链表2 头插法 在头结点之后插新结点 插过之后倒序

void CreateFromHead(LinkList L)
{
    Node *s;
    char c ;
    int flag=1 ;
    while (flag)
    {
        c= getchar();
        if(c!='$')
        {
            s=(Node *)malloc(sizeof(Node));
            s->data =c ; //赋值给结点的值域
            s->next= L->next;
            L->next= s;
        }
        else flag=0;
    }
}

//单链表3 尾插法 在链后面加新结点 正常顺序

void CreateFromTail(LinkList L)
{
    Node *s,*r;
    char c ;
    int flag=1 ;
    r=L;  // 这个注意，定义r指针的时候要把它指向L；
    while (flag)
    {
        c= getchar();
        if(c!='$')
        {
            s=(Node *)malloc(sizeof(Node));
            s->data =c ; //赋值给结点的值域
           r->next= s;
            r=s;
          // s->next =NULL; //这个地方不需要马上清空，可以等输入到最后再做
        }
        else {flag=0;
            r->next= NULL;//最后结点尾部置空
        }
    }
}

// 头插尾插都是形成链表用的

//单链表4 查找 按序号查找 这个地方的序号就很容易和数组的下标区别开了
//但也因为不再是像线性存储那样空间连续，所以要遍历查找，需要一个计数器j

Node * Get(LinkList L, int i )
//找到就返回存储位置，找不到返回NULL 都要考虑找到和找不到的情况
{
    int j ;
    Node *p;
    p=L;
    j=0;
    while ((p->next!=NULL)&&(j<i)) // 如果没到结尾也没错过去，就再往后找
    {
        p=p->next;
        j++;
    }
    if(i==j) return p ;
    else return NULL;
}


//单链表4.5 查找2 按值查找
Node *Locate(LinkList L , ElemType key )
{
    Node *p ;
    p= L->next ;
    while (p!=NULL) //在到头之前，没找到就后移，找到就退出循环
    {
        if (p->data != key ) p=p->next;
        else break ;
    }
    return p ; // 输出地址
}

//单链表5 求单链表的长度
int ListLength(LinkList L)
{
    Node *p ;
    int j;
    p=L->next;
    j=0 ;
    while(p!=NULL) // 从头到位走一遍，j计数
    {
         p=p->next; // 指针后移
         j++;  // 查数
        
    }
        return j ;
}

//单链表6 插入 这个插入指的是链表已经形成之后，想从链表中间插入元素的情形
int InsList (LinkList L , int i, ElemType e )//要在序号为i的位置上插入元素,e是这个插入元素的值
{
    Node *pre , *s;
    int k ; pre=L; k=0;
    while (pre!=NULL&&k<i-1) //先找到i-1,注意这个地方和删除是不一样的，因为插入的话，尾后也可以插入
    {
        pre=pre->next;
        k=k+1;
    }
    if (!pre)//如果为空，说明是非法插入
    {printf("插入位置不合理。");
        return ERROR ;
    }
    
    s=(Node *)malloc(sizeof(Node));
    s->data = e;
    s->next= pre->next;
    pre->next = s ;
    return OK ;
}

//单链表7 按位置删除
int DelList (LinkList L , int i, ElemType *e )//想删掉哪个位置的值，把删掉的值带回主函数，不明白e有什么作用，这个调用的时候不是要传参数吗？
{ Node *pre , *r;
    int k ; pre=L; k=0;
    while (pre->next!=NULL&&k<i-1) //先找到i-1,
    {
        pre=pre->next;
        k=k+1;
    }
    if (!pre)//如果为空，说明是非法位置
    {printf("删除位置不合理。");
        return ERROR ;
    }
    
    r=pre->next;
    pre->next= pre->next->next;
    *e= r->data;
    
    free(r);// #include <stdlib.h> 这个地方，如果不放进这个头文件，这个释放函数是用不了的
    printf("删除成功。");
    return OK ;
}

//单链表8 合并 这个时候就不用再创建第三个链表了，两个链表结点组合就OK

LinkList MergeLinkList(LinkList LA,LinkList LB)
{
    Node *pa,*pb;
    Node *r;
    LinkList LC;
    pa =LA->next;
    pb = LB->next;
    LC= LA ;
    LC->next = NULL;
    r=LC ;
    while (pa!=NULL&&pb!=NULL)
    {
        if(pa->data<= pb->data)
        {
            r->next=pa;
            r= pa;
            pa= pa->next;
        }
        else
        {
            r->next= pb;
            r=pb;
            pb=pb->next;
        }
    }
    
//    while (pa!=NULL)
//    {
    //        r= pa->next;这又搞错了 是让元素链接到新表的后面 所以是 r->next= pa;
//    }
//
//    while (pb!=NULL)
//    {
//        r= pb->next;
//    }
    if(pa) r->next=pa; // 这个是判断最后谁还有剩余，谁剩下的话就把剩余的元素接到新表后买呢
    else r->next =pb;
    
    free(LB);//因为是把LA作为LC的基底了，所以最后释放LB
    return (LC);
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    LinkList L ;// 一个指针
    LinkList La;
    LinkList Lb;
    Init_LinkList(&La);
    Init_LinkList(&Lb);
    int  i;
    i= Init_LinkList(&L);// 这个是指针的地址，正确使用函数名 注意一下自己的定义的函数名字
   // printf("链表L初始化完成，ListLength(L) %d\n",ListLength(L));
    CreateFromHead(La);
    CreateFromHead(Lb);
    int k ;
    k= ListLength(MergeLinkList(La, Lb));
  printf("ListLength(Lc) %d\n", k);
    return 0;
}
