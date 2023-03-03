#include <stdio.h>
#include <string.h>
#include <time.h>
#include "llist.h"
#include "bst.h"

struct ll_node* head = NULL;
struct node* root = NULL;

char dataInputFilename[] = "log_input.txt";
char dataOutputFilename1[] = "change_log.txt";
char dataOutputFilename2[] = "log_present.txt";

int docfile(ll_node** head) {
  FILE *f = fopen(dataInputFilename, "r");
  int n = 0;
  char date[11];
  char time[9];
  char license[13];
  int status;

  while (fscanf(f, "%10s %8s %12s %d", date, time, license, &status) != EOF) {
    push(&(*head), date, time, license, status);
    n++;
  }

  fclose(f);
  return n;
}

void soluong_gui_lay(ll_node* node, char date[], int N) {
    int so_xe_lay = 0;
    int so_xe_gui = 0;
    for (int i = 0; i < N; i++) {
        if(strcmp(date, node->date) == 0){
            if(node->status == 0){
                so_xe_lay++;
            }
            else
                so_xe_gui++;
        }
        node = node->next;
    }
    printf("Date %s Total %d, In %d, out %d\n", date, so_xe_gui+so_xe_lay, so_xe_gui, so_xe_lay);
}

void loc_va_insert(ll_node* Node, node **root, int N) {
    ll_node* head = Node;
    while(Node->next != NULL) {
        int times = 0;
        ll_node *temp = Node;
        temp = head;
        while(temp != NULL) {
            if(strcmp(Node->license, temp->license) == 0){
                times++;
            }
            temp = temp->next;
        }

        if(times % 2 == 1) {
            insert(&(*root), Node->license, Node->date, Node->time);
        }
        Node = Node->next;
    }
}

void printTime()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Hien tai la: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1,
    tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int main() {
  int N;
  int option = 1;
  char date[11];
  char license[13];

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  int soxe;

  char file_date[11];
  char file_time[9];
  sprintf(file_date, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
  sprintf(file_time, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);

  while (option != 8)
  {
    printf("Chuong trinh quan ly bai xe\nVui long chon mot trong cac chuc nang sau\n[1] Doc du lieu tu file log\n[2] Tra cuu so luong xe gui/lay theo ngay trong qua khu\n[3] Thong tin cac xe trong bai hien tai\n[4] Gui them xe moi\n[5] Tra xe\n[6] In cay\n[7] Luu danh sach xe dang co trong bai ra file\n[8] Thoat\nLua chon cua ban la:\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        N = docfile(&head);
        printf("Tong so %d ban ghi\n", N);
        printf("Doc du lieu thanh cong.\n");
        break;
    case 2:
        printf("Nhap ngay can tra: ");
        scanf("%s", date);
        soluong_gui_lay(head, date, N);
        break;
    case 3:
        loc_va_insert(head, &root, N);
        soxe = count_tree(root);
        printf("Tong so xe hien co: %d\n", soxe);
        printf("Bien so \t Thoi gian gui\n");
        inorder(root);
        break;
    case 4:
        printf("Nhap bien so xe: ");
        scanf("%s", license);
        if (da_co_xe(root, license) == 1) {
            printf("%s : Loi bien so da ton tai\n", license);
        }
        else{
            gui_xe(&root, license, file_date, file_time);
            printf("%s : Gui xe thanh cong %s %s\n", license, file_date, file_time);
            FILE *f = fopen(dataOutputFilename1, "a");
            fprintf(f, "%s %s %s %d\n", file_date, file_time, license, 1);
            fclose(f);
        }
        break;
    case 5:
        printf("Nhap bien so xe: ");
        scanf("%s", license);
        if (da_co_xe(root, license) != 1) {
            printf("%s : Lay xe KHONG thanh cong do xe khong gui tai bai\n", license);
        }
        else {
            deleteNode(&root, license);
            printf("%s : Lay xe thanh cong\n", license);
            FILE *f = fopen(dataOutputFilename1, "a");
            fprintf(f, "%s %s %s %d\n", file_date, file_time, license, 0);
            fclose(f);
        }    
        break;
    case 6:
        inorder(root);       
        break;
    case 7:
        remove(dataOutputFilename2);
        luu_ra_file(root, dataOutputFilename2);
        printf("Luu thanh cong.\n");
        break;
    }
  }

  freeTree(&root);
  return 0;
}