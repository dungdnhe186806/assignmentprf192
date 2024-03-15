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

void themSinhVien(struct SinhVien students[], int *soLuong) {
    if (*soLuong >= MAX_STUDENTS) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }

    printf("Nhap thong tin sinh vien moi:\n");
    printf("ID: ");
    scanf("%s", students[*soLuong].id);
    fflush(stdin); // Xóa bộ nhớ đệm stdin
    printf("Ho Ten: ");
    scanf("%s", students[*soLuong].ten);
    fflush(stdin); 
    printf("Nam Sinh: ");
    scanf("%d", &students[*soLuong].namSinh);
    fflush(stdin); 
    printf("Que Quan: ");
    scanf("%s", students[*soLuong].queQuan);
    fflush(stdin); 

    (*soLuong)++;
}

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




void capNhatSinhVien(struct SinhVien students[], int soLuong) {
    char timID[20];
    printf("Nhap ID cua sinh vien can cap nhat: ");
    scanf("%s", timID);
    fflush(stdin); // Xóa bộ nhớ đệm stdin

    for (int i = 0; i < soLuong; i++) {
        if (strcmp(students[i].id, timID) == 0) {
            printf("Nhap thong tin moi cho sinh vien:\n");
            printf("Ten moi: ");
            scanf("%s", students[i].ten);
            fflush(stdin); 
            printf("Nam Sinh moi: ");
            scanf("%d", &students[i].namSinh);
            fflush(stdin);  
            printf("Que Quan moi: ");
            scanf("%s", students[i].queQuan);
            fflush(stdin);  
            printf("Thong tin sinh vien da duoc cap nhat.\n");
            return;
        }
    }

    printf("Khong tim thay sinh vien voi ID nay.\n");
}

void xoaSinhVien(struct SinhVien students[], int *soLuong) {
    char timID[20];
    printf("Nhap ID cua sinh vien can xoa: ");
    scanf("%s", timID);
    fflush(stdin);  

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

void luuVaoTep(struct SinhVien students[], int soLuong, const char *tenTep) {
    FILE *tep = fopen(tenTep, "r"); // Mở tệp để đọc
    if (tep == NULL) {
        printf("Khong the mo tep %s de ghi.\n", tenTep);
        return;
    }

    // Đọc và lưu dòng đầu tiên vào một biến tạm
    char line[100];
    fgets(line, sizeof(line), tep);

    fclose(tep); // Đóng tệp

    // Mở tệp để ghi dữ liệu mới vào
    tep = fopen(tenTep, "w");
    if (tep == NULL) {
        printf("Khong the mo tep %s de ghi.\n", tenTep);
        return;
    }

    // Ghi dòng đầu tiên vào tệp
    fprintf(tep, "%s", line);

    // Ghi dữ liệu sinh viên vào từ hàng thứ 2
    for (int i = 0; i < soLuong; i++) {
        fprintf(tep, "%s %s %d %s\n", students[i].id, students[i].ten, students[i].namSinh, students[i].queQuan);
    }

    fclose(tep);
    printf("Du lieu da duoc luu vao tep %s.\n", tenTep);
}



void taiTuTep(struct SinhVien students[], int *soLuong, const char *tenTep) {
    FILE *tep = fopen(tenTep, "r");
    if (tep == NULL) {
        printf("Khong the mo tep %s de doc.\n", tenTep);
        return;
    }

    char line[100]; // Để lưu trữ dòng dữ liệu từ file
    fgets(line, sizeof(line), tep); // Bỏ qua dòng đầu tiên

    *soLuong = 0;
    while (fgets(line, sizeof(line), tep) != NULL) {
        sscanf(line, "%s %s %d %s", students[*soLuong].id, students[*soLuong].ten, &students[*soLuong].namSinh, students[*soLuong].queQuan);
        (*soLuong)++;
    }

    fclose(tep);
    printf("Du lieu da duoc tai tu tep %s.\n", tenTep);
}


int main() {
    struct SinhVien students[MAX_STUDENTS];
    int soLuong = 0;
    char tenTep[] = "data.txt";

    taiTuTep(students, &soLuong, tenTep);

    int luaChon;
    do {
        printf("\n----- Menu -----\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Cap nhat thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Luu du lieu vao tep\n");
        printf("6. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        fflush(stdin);  

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
                luuVaoTep(students, soLuong, tenTep);
                break;
            case 6:
                luuVaoTep(students, soLuong, tenTep);
                printf("Chuong trinh da ket thuc.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 6);

    return 0;
}
