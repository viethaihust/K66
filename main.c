#include <stdio.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "bst.h"

struct node* root = NULL;

const char dataFilename[] = "log_input.txt";

int docfile(struct cp_t data[]) {
  FILE *f = fopen(dataFilename, "r");
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

  while (option != 6)
  {
    printf("Chuong trinh quan ly bai xe\nVui long chon mot trong cac chuc nang sau\n[1] Doc du lieu tu file log\n[2] Tra cuu so luong xe gui/lay theo ngay trong qua khu\n[3] Thong tin cac xe trong bai hien tai\n[4] Gui them xe moi\n[5] Tra xe\n[6] Thoat\nLua chon cua ban la:\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        N = docfile(data);
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
        char date[11];
        char time[9];
        sprintf(date, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        sprintf(time, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
        gui_xe(&root, license, date, time);
        break;
    case 5:
        freeTree(&root);
        inorder(root);       
        break;
    }
  }
  return 0;
}