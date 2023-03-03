#include <stdio.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "bst.h"

struct node* root = NULL;

const char dataInputFilename[] = "log_input.txt";
const char dataOutputFilename[] = "change_log.txt";

int docfile(struct cp_t data[]) {
  FILE *f = fopen(dataInputFilename, "r");
  int n = 0;

  while (fscanf(f, "%10s %8s %12s %d", data[n].date, data[n].time, data[n].license, &data[n].status) != EOF) {
    n++;
  }

  fclose(f);
  return n;
}

void hienthi(struct cp_t data[], const int N) {
  for (int i = 0; i < N; i++) {
    printf("%s %s %s %d\n", data[i].date, data[i].time, data[i].license, data[i].status);
    printf("\n");
  }
}

void soluong_gui_lay(struct cp_t data[], char date[], int N) {
    int so_xe_lay = 0;
    int so_xe_gui = 0;
    for (int i = 0; i < N; i++) {
        if(strcmp(date, data[i].date) == 0){
            if(data[i].status == 0){
                so_xe_lay++;
            }
            else
                so_xe_gui++;
        }
    }
    printf("Date %s Total %d, In %d, out %d\n", date, so_xe_gui+so_xe_lay, so_xe_gui, so_xe_lay);
}

void loc_va_insert(struct cp_t data[], node **root, int N) {
    for (int i = N; i > 0; i--) {
        int times = 0;
        for(int j = 0; j < N; j++) {
            if(strcmp(data[i].license, data[j].license) == 0){
                times++;
            }
        }
        if(times % 2 == 1) {
            insert(&(*root), data[i].license, data[i].date, data[i].time);
        }
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
  struct cp_t data[512];
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

  while (option != 7)
  {
    printf("Chuong trinh quan ly bai xe\nVui long chon mot trong cac chuc nang sau\n[1] Doc du lieu tu file log\n[2] Tra cuu so luong xe gui/lay theo ngay trong qua khu\n[3] Thong tin cac xe trong bai hien tai\n[4] Gui them xe moi\n[5] Tra xe\n[6] In cay\n[7] Thoat\nLua chon cua ban la:\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        N = docfile(data);
        printf("Doc du lieu thanh cong.\n");
        break;
    case 2:
        printf("Nhap ngay can tra: ");
        scanf("%s", date);
        soluong_gui_lay(data, date, N);
        break;
    case 3:
        loc_va_insert(data, &root, N);
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
            FILE *f = fopen(dataOutputFilename, "a");
            fprintf(f, "%s %s %s %d\n", file_date, file_time, license, 1);
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
            FILE *f = fopen(dataOutputFilename, "a");
            fprintf(f, "%s %s %s %d\n", file_date, file_time, license, 0);
        }    
        break;
    case 6:
        inorder(root);       
        break;
    }
  }
  return 0;
}