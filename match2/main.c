//
//  main.c
//  match2
//
//  Created by 20161104566 on 18/6/27.
//  Copyright © 2018年 20161104566. All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>
typedef struct Singer
{
    char name[20];
    int number;
    char sex;
    float score[9];
    float average;
    struct Singer *next;
}SINGER;
SINGER*CreateLink(int number)
{
    SINGER *head;
    SINGER *tail;
    SINGER *NewNode=NULL;
    FILE *fp;
    int n;
    head=(SINGER*)malloc(sizeof(SINGER));
    head->next=NULL;
    tail=head;
    fp=fopen("singerOriginal.dat","wb");
    for(n=0;n<number;n++)
    {
        NewNode=(SINGER*)malloc(sizeof(SINGER));
        NewNode->next=NULL;
        tail->next=NewNode;
        fwrite(NewNode,sizeof(SINGER),1,fp);
    }
    NewNode=NULL;
    fclose(fp);
    return head;
}
void InputData(SINGER *s)
{
    FILE *fp;
    int n;
    int m;
    SINGER *h=s->next;
    fp=fopen("singerOriginal.dat","wb");
    while(1)
    {
        if(h==NULL)
        {
            return;
        }
        printf("请输入%d个选手的信息:\n",m);
        printf("请输入姓名:");
        scanf("%s",h->name);
        printf("请输入编号:");
        scanf("%d",&(h->number));
        getchar();
        printf("请输入成绩:\n");
        for(n=0;n<10;n++)
        {
            printf("请输入第%d个评委的打分:",n+1);
            scanf("%f",&(h->score[n]));
        }
        printf("********************************************************************\n");
        printf("***************************************************************************\n");
        h=h->next;
        m++;
        fwrite(s,sizeof(SINGER),1,fp);
    }
    fclose(fp);
}
void CalculateData(SINGER *s)
{
    int n;
    float min;
    float max;
    SINGER *h=s->next;
    while(1)
    {
        if(h==NULL)
        {
            return;
        }
        max=h->score[0];
        min=max;
        h->average=0;
        for(n=0;n<9;n++)
        {
            if(h->score[n]>max)
            {
                max=h->score[n];
            }
            if(h->score[n]<min)
            {
                min=h->score[n];
            }
        }
        for(n=0;n<9;n++)
        {
            (h->average)+=(h->score[n]);
        }
        h->average=(float)((h->average-max-min)/8.0);
        h=h->next;
    }
}
void SortData(SINGER *s,int number)
{
    SINGER *head,*tail;
    SINGER *p,*p1,*p2,*p3;
    int n;
    tail=(SINGER*)malloc(sizeof(SINGER));
    head=s;
    p=s->next;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    p->next=tail;
    tail->next=NULL;
    for(n=0;n<number-1;n++)
    {
        p3=head;
        p1=p3->next;
        p2=p1->next;
        while(p2!=tail)
        {
            if((p1->average)<(p2->average))
            {
                p1->next=p2->next;
                p2->next=p1;
                p3->next=p2;
                p3=p2;
                p2=p1->next;
            }
            else
            {
                p3=p1;
                p1=p2;
                p2=p2->next;
            }
        }
    }
    p=s->next;
    while(p->next!=tail)
    {
        p=p->next;
    }
    p->next=NULL;
}
/*****************************输出数据源函数OutputSource()*************************/
void OutputSource(SINGER *s)
{
        SINGER *h=s->next;
        int n;
        printf("下面输出原始成绩:\n");
        printf("选手编号 姓名 评委打分\n");
        while(1)
        {
            if(h==NULL)
            {
                 return;
            }
            printf("%d %s",h->number,h->name);
            for(n=0;n<9;n++)
            {
                printf("%.3f",h->score[n]);
            }
            printf("\n");
            h=h->next;
        }
}
/*****************************输出最终数据OutputFinal()*************************/
void OutputFinal(SINGER *s)
{
    FILE *fp;
    SINGER *h=s->next;
    int n=1;
    printf("下面输出最终成绩:\n");
    printf("名次 选手编号 姓名 得分\n");
    fopen("singerFinal.dat","wb");
    while(1)
    {
        if(h==NULL)
        {
            return;
        }
        printf("%d  %d  %s  %.3f",n,h->number,h->name,h->average);
        n++;
        printf("\n");
        h=h->next;
    }
    fclose(fp);
}
/*****************************删除数据Delete()*************************/
SINGER* Delete(SINGER *s)
{
    int SN;
    SINGER *p1=NULL;
    SINGER *p2=NULL;
    p1=s->next;
    printf("请输入你想删除的歌手的编号");
    scanf("%d",&SN);
    while(SN!=p1->number&&p1->next!=NULL)
    {
        p2=p1;
        p1=p1->next;
    }
    if(p1->number==SN)
    {
        if(p1==s->next)
        {
            s=p1;
            p1=NULL;
        }
        else
        {
            p2->next=p1->next;
            free(p1);
        }
        return s;
    }
    else
    {
        printf("无此名歌手\n");
    }
    return s;
}
/*****************************插入数据insert()*************************/
void insert(SINGER *head,SINGER *p)
{
    SINGER *s=(SINGER*)malloc(sizeof(SINGER));
    for(s=head;s->next!=NULL;)
    {
        s=s->next;
    }
    s->next=p;
    p->next=NULL;
}
/*****************************主函数main()*************************/
int main(void)
{
    SINGER *head;
    int SingerNumber;
    int instruct;
    int n;
    printf("********************************************************\n");
    printf("歌手评分系统\n");
    printf("\n\n");
    printf("下面开始创建歌手信息\n");
    printf("请输入歌手人数:");
    scanf("%d",&SingerNumber);
    head=CreateLink(SingerNumber);
    printf("下面请输入歌手信息\n");
    InputData(head);
    OutputSource(head);
    printf("********************************************************\n");
    printf("********************************************************\n");
    printf("请输入操作指令:\n");
    while(1)
    {
        printf("插入个人信息请按:“1”\n");
        printf("删除个人信息请按:“2”\n");
        printf("计算成绩请按:“3”\n");
        printf("计算排名请按:“4”\n");
        printf("输出最终成绩请按:“5”\n");
        printf("退出请按:“6”\n");
        printf("请输入操作指令:");
        scanf("%d",&instruct);
        if(instruct==1)
        {
            SINGER *p = (SINGER*)malloc(sizeof(SINGER));
            printf("请输入要插入的歌手信息");
            printf("请输入姓名:");
            scanf("%s",p->name);
            printf("请输入编号:");
            scanf("%d",&(p->number));
            getchar();
            insert(head,p);
            SingerNumber++;
            printf("请输入成绩:\n");
            for(n=0;n<9;n++)
            {
                printf("请输入第%d个评委的打分:",n+1);
                scanf("%f",&(p->score[n]));
            }
            printf("插入完成，请继续操作:\n");
            printf("********************************************************\n");
            printf("********************************************************\n");
        }
        else if(instruct==2)
        {
            head=Delete(head);
            printf("删除完成，请继续操作:\n");
            printf("********************************************************\n");
            printf("********************************************************\n");
        }
        else if(instruct==4)
        {
            SortData(head,SingerNumber);
            printf("排序完成,请继续操作:\n");
            printf("********************************************************\n");
            printf("********************************************************\n");
        }
        else if(instruct==5)
        {
            OutputFinal(head);
            printf("输出完成，请继续操作:\n");
            printf("********************************************************\n");
            printf("********************************************************\n");
        }
        else if(instruct==6)
        {
            break;
        }
        else
        {
            printf("输入有误，请重新输入:\n");
            printf("********************************************************\n");
            printf("********************************************************\n");
        }
    }
    return 0;
}
