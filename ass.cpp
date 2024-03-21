#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

struct SinhVien {
    char id[20];
    char ten[50];
    int namSinh;
    char queQuan[50];
};
// Them sinh vien 
void themSinhVien(struct SinhVien students[], int *soLuong) {
    if (*soLuong >= MAX_STUDENTS) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }

    printf("Nhap thong tin sinh vien moi:\n");
    printf("ID: ");
    scanf("%s", students[*soLuong].id);

    printf("Ho Ten: ");
    scanf(" %[^\n]", students[*soLuong].ten); 

    printf("Nam Sinh: ");
    scanf("%d", &students[*soLuong].namSinh);

    printf("Que Quan: ");
    scanf(" %[^\n]", students[*soLuong].queQuan); 

    (*soLuong)++;
    printf("Them thong tin thanh cong.\n");
}


// Hien thi sinh vien

void hienThiSinhVien(struct SinhVien students[], int soLuong) {
    if (soLuong == 0) {
        printf("Danh sach sinh vien trong.\n");
        return;
    }

    printf("+------+----------------------+----------------------------+-----------------+--------------------+\n");
    printf("|  STT |         ID           |           Ho Ten           |    Nam Sinh     |       Que Quan     |\n");
    printf("+------+----------------------+----------------------------+-----------------+--------------------+\n");
    for (int i = 0; i < soLuong; i++) {
        printf("| %-4d | %-20s | %-26s | %-15d | %-18s |\n", i + 1, students[i].id, students[i].ten, students[i].namSinh, students[i].queQuan);
    }
    printf("+------+----------------------+----------------------------+-----------------+--------------------+\n");
}

// Cap nhat thong tin sinh vien
void capNhatSinhVien(struct SinhVien students[], int soLuong) {
    char timID[20];
    printf("Nhap ID cua sinh vien can cap nhat: ");
    scanf("%s", timID);

    for (int i = 0; i < soLuong; i++) {
        if (strcmp(students[i].id, timID) == 0) {
            printf("Nhap thong tin moi cho sinh vien:\n");
            printf("Ten moi: ");
            scanf(" %[^\n]", students[i].ten); // Sửa thông tin họ tên
            
            printf("Nam Sinh moi: ");
            scanf("%d", &students[i].namSinh);
       
            printf("Que Quan moi: ");
            scanf(" %[^\n]", students[i].queQuan); // Sửa thông tin quê quán
            
            printf("Thong tin sinh vien da duoc cap nhat.\n");
            return;
        }
    }

    printf("Khong tim thay sinh vien voi ID nay.\n");
}


// Xoa sinh vien

void xoaSinhVien(struct SinhVien students[], int *soLuong) {
    char timID[20];
    printf("Nhap ID cua sinh vien can xoa: ");
    scanf("%s", timID);
      

    for (int i = 0; i < *soLuong; i++) {
        if (strcmp(students[i].id, timID) == 0) {
            for (int j = i; j < *soLuong - 1; j++) {
                strcpy(students[j].id, students[j + 1].id);
                strcpy(students[j].ten, students[j + 1].ten);
                students[j].namSinh = students[j + 1].namSinh;
                strcpy(students[j].queQuan, students[j + 1].queQuan);
            }
            (*soLuong)--;
            printf("Sinh vien da duoc xoa.\n");
            return;
        }
    }

    printf("Khong tim thay sinh vien voi ID nay.\n");
}

// Luu thong tin vao tep
void luuVaoTep(struct SinhVien students[], int soLuong, const char *tenTep) {
    FILE *tep = fopen(tenTep, "w");
    if (tep == NULL) {
        printf("Khong the mo tep %s de ghi.\n", tenTep);
        return;
    }

    fprintf(tep, "ID Ho_Ten Nam_Sinh Que_Quan\n");
    for (int i = 0; i < soLuong; i++) {
        fprintf(tep, "%s %s %d %s\n", students[i].id, students[i].ten, students[i].namSinh, students[i].queQuan);
    }

    fclose(tep);
    printf("Du lieu da duoc luu vao tep %s.\n", tenTep);
}

// Tai du lieu tu tep
void taiTuTep(struct SinhVien students[], int *soLuong, const char *tenTep) {
    FILE *tep = fopen(tenTep, "r");
    if (tep == NULL) {
        printf("Khong the mo tep %s de doc.\n", tenTep);
        return;
    }

    char line[100];
    fgets(line, sizeof(line), tep);

    *soLuong = 0;
    while (fgets(line, sizeof(line), tep) != NULL) {
        sscanf(line, "%s %s %d %s", students[*soLuong].id, students[*soLuong].ten, &students[*soLuong].namSinh, students[*soLuong].queQuan);
        (*soLuong)++;
    }

    fclose(tep);
    printf("Du lieu da duoc tai tu tep %s.\n", tenTep);
}

// Thay doi vi tri cac sinh vien
void hoanDoiViTri(struct SinhVien *a, struct SinhVien *b) {
    struct SinhVien temp = *a;
    *a = *b;
    *b = temp;
}

void thayDoiViTri(struct SinhVien students[], int soLuong) {
    int viTri1, viTri2;
    printf("Nhap vi tri cua sinh vien 1: ");
    scanf("%d", &viTri1);
    printf("Nhap vi tri cua sinh vien 2: ");
    scanf("%d", &viTri2);

    if (viTri1 < 1 || viTri1 > soLuong || viTri2 < 1 || viTri2 > soLuong) {
        printf("Vi tri nhap vao khong hop le.\n");
        return;
    }

    hoanDoiViTri(&students[viTri1 - 1], &students[viTri2 - 1]);
    printf("Da thay doi vi tri cua sinh vien.\n");
}

int main() {
    struct SinhVien students[MAX_STUDENTS];
    int soLuong = 0;
    char data[] = "data.txt";

    taiTuTep(students, &soLuong, data);

    int luaChon;
    do {
        printf("\n----- Menu -----\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Cap nhat thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Luu du lieu vao tep\n");
        printf("6. Thay doi vi tri sinh vien\n");
        printf("7. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                themSinhVien(students, &soLuong);
                break;
            case 2:
                hienThiSinhVien(students, soLuong);
                break;
            case 3:
                capNhatSinhVien(students, soLuong);
                break;
            case 4:
                xoaSinhVien(students, &soLuong);
                break;
            case 5:
                luuVaoTep(students, soLuong, data);
                break;
            case 6:
                thayDoiViTri(students, soLuong);
                break;
            case 7:
                luuVaoTep(students, soLuong, data);
                printf("Chuong trinh da ket thuc.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 7);

    return 0;
}
