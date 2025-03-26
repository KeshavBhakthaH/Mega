#include<stdio.h>
struct process{
    int id,bt,wt,tat;
};

void sort(struct process p[],int n){
    struct process temp;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(p[i].bt>p[j].bt){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}
void cal(struct process p[],int n){
    p[0].wt=0;
    for(int i=1;i<n;i++){
        p[i].wt=p[i-1].wt+p[i-1].bt;
    }
    for(int i=0;i<n;i++){
        p[i].tat=p[i].wt+p[i].bt;
    }
}
void display(struct process p[],int n){
    float avg_wt=0,avg_tat=0;
    //int tot_wt=0,tot_tat=0;
    printf("id\tbt\twt\ttat\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n",p[i].id,p[i].bt,p[i].wt,p[i].tat);
        avg_wt+=p[i].wt;
        avg_tat+=p[i].tat;
    }
    printf("total waiting time : %f\navg waiting time : %f\ntotal turnaround time : %f\navg turnaround time : %f\n",avg_wt,avg_wt/n,avg_tat,avg_tat/n);
}
void main(){
    int n;
    printf("enter the number of process : ");
    scanf("%d",&n);
    struct process p[n];
    for(int i=0;i<n;i++){
        printf("process id : %d ",i+1);
        printf("process bt : ");
        scanf("%d",&p[i].bt);
        p[i].id=i+1;
    }
    sort(p,n);
    cal(p,n);
    display(p,n);
}