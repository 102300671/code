#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生结构体
typedef struct Student {
    char name[10];
    char studentId[13];
    double score[7]; // 各科成绩 (0-4)、总分 (5)、平均分 (6)
    struct Student *next;
} Student;

// 班级结构体
typedef struct Class {
    char classname[10];
    Student *head;
    Student *tail;
} Class;

// 函数声明
Class *createClass(char *classname);
int addStudent(Class *classes, char *name, char *studentId, double *score);
void printClass(Class *classes);
void searchScore(Class *classes, int courseIndex, double searchScore);
void searchName(Class *classes, char *name);
void changeStudentInfo(Class *classes, char *studentId);
void deleteStudent(Class *classes, char *studentId);
int insertStudent(Class *classes, char *name, char *studentId, double *score);
void sortClassByScore(Class *classes, int courseIndex);
void clearBuffer();
void freeClassMemory(Class **classes, int classCount);

// 工具函数
void printStudentInfo(Student *student);
void swap(Student *a, Student *b);

// 主函数
int main() {
    int classCount;
    printf("请输入班级数量: ");
    scanf("%d", &classCount);
    clearBuffer();

    Class **classes = (Class **)malloc(classCount * sizeof(Class *));
    if (classes == NULL) {
        printf("内存分配失败！\n");
        return 1;
    }

    int currentClassCount = 0;
    while (1) {
        char classname[10];
        printf("请选择班级 (不存在则创建)，退出请输入 0: ");
        fgets(classname, 10, stdin);
        classname[strcspn(classname, "\n")] = 0; // 去除换行符

        if (strcmp(classname, "0") == 0) break;

        int classIndex = -1;
        for (int i = 0; i < currentClassCount; i++) {
            if (strcmp(classes[i]->classname, classname) == 0) {
                classIndex = i;
                break;
            }
        }

        if (classIndex == -1) {
            if (currentClassCount >= classCount) {
                printf("班级数量已达上限，无法创建更多班级！\n");
                continue;
            }
            classes[currentClassCount] = createClass(classname);
            classIndex = currentClassCount++;
        }

        char manage;
        printf("是否管理此班级？(Y/n): ");
        scanf(" %c", &manage);
        clearBuffer();

        if (manage == 'Y' || manage == 'y') {
            while (1) {
                printf("1: 成绩录入\n2: 成绩输出\n3: 按成绩查询\n4: 按姓名查询\n"
                       "5：修改学生信息\n6: 按成绩排序\n7: 删除学生\n8: 向已排序班级中插入学生\n"
                       "9: 输出总分大于特定值的学生\n10: 切换班级及退出\n");
                printf("请选择操作: ");
                int option;
                scanf("%d", &option);
                clearBuffer();
                
                if (option == 1) {
                    int studentCount;
                    printf("请输入学生数量: ");
                    scanf("%d", &studentCount);
                    clearBuffer();

                    for (int i = 0; i < studentCount; i++) {
                        char name[10];
                        char studentId[13];
                        double score[5];

                        printf("请输入姓名 学号: ");
                        scanf("%s %s", name, studentId);
                        printf("请输入5门课程成绩 (高数、英语、C语言、导论、思政): ");
                        for (int j = 0; j < 5; j++) {
                            scanf("%lf", &score[j]);
                        }
                        addStudent(classes[classIndex], name, studentId, score);
                    }
                } else if (option == 2) {
                    printClass(classes[classIndex]);
                } else if (option == 3) {
                    int courseIndex;
                    double searchscore;
                    printf("高数:0 英语:1 C语言:2 导论:3 思政:4\n");
                    printf("输入课程索引 (0-4) 或 总分(5) 或 平均分(6): ");
                    scanf("%d", &courseIndex);
                    printf("输入要查询的成绩: ");
                    scanf("%lf", &searchscore);
                    searchScore(classes[classIndex], courseIndex, searchscore);
                } else if (option == 4) {
                    char name[10];
                    printf("输入学生姓名: ");
                    fgets(name, 10, stdin);
                    name[strcspn(name, "\n")] = 0; // 去除换行符
                    searchName(classes[classIndex], name);
                } else if (option == 5) {
                    char studentId[13];
                    printf("输入学生学号: ");
                    scanf("%s", studentId);
                    changeStudentInfo(classes[classIndex], studentId);
                } else if (option == 6) {
                    int courseIndex;
                    printf("输入课程索引 (0-4) 或 总分(5) 或 平均分(6): \n");
                    printf("高数:0 英语:1 C语言:2 导论:3 思政:4\n");
                    scanf("%d", &courseIndex);
                    sortClassByScore(classes[classIndex], courseIndex);
                    printClass(classes[classIndex]);
                } else if (option == 7) {
                    char studentId[13];
                    printf("输入学生学号: ");
                    scanf("%s", studentId);
                    deleteStudent(classes[classIndex], studentId);
                } else if (option == 8) {
                    char name[10];
                    char studentId[13];
                    double score[5];
                    printf("输入姓名 学号: ");
                    scanf("%s %s", name, studentId);
                    printf("输入5门课程成绩(高数、英语、C语言、导论、思政): ");
                    for (int j = 0; j < 5; j++) {
                        scanf("%lf", &score[j]);
                    }
                    insertStudent(classes[classIndex], name, studentId, score);
                } else if (option == 9) {
                    double totalScore;
                    int found = 0;
                    printf("输入要查询的总分: ");
                    scanf("%lf", &totalScore);
                    Student *current = classes[classIndex]->head;
                    printf("%-10s %-12s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
                           "姓名", "学号", "高数", "英语", "C语言",
                           "导论", "思政", "总分", "平均分");
                    while (current) {
                        if (current->score[5] > totalScore) {
                            printStudentInfo(current);
                            found++;
                        }
                        current = current->next;
                    }
                    if(found == 0) {
                            printf("无符合条件的学生。\n");
                        } else {
                            printf("共找到 %d 个学生。\n", found);
                        }
                } else if (option == 10) {
                    break;
                }
            }
        }
    }

    freeClassMemory(classes, currentClassCount);
    return 0;
}

// 清除输入缓冲区
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 创建班级
Class *createClass(char *classname) {
    Class *newClass = (Class *)malloc(sizeof(Class));
    if (newClass == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    strcpy(newClass->classname, classname);
    newClass->head = NULL;
    newClass->tail = NULL;
    return newClass;
}

// 添加学生
int addStudent(Class *classes, char *name, char *studentId, double *score) {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("内存分配失败！\n");
        return 0;
    }

    strcpy(newStudent->name, name);
    strcpy(newStudent->studentId, studentId);

    double totalScore = 0;
    for (int i = 0; i < 5; i++) {
        newStudent->score[i] = score[i];
        totalScore += score[i];
    }
    newStudent->score[5] = totalScore;
    newStudent->score[6] = totalScore / 5;
    newStudent->next = NULL;

    if (classes->head == NULL) {
        classes->head = newStudent;
        classes->tail = newStudent;
    } else {
        classes->tail->next = newStudent;
        classes->tail = newStudent;
    }
    return 1;
}

// 打印学生信息
void printStudentInfo(Student *student) {
    printf("%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
           student->name, student->studentId,
           student->score[0], student->score[1], student->score[2],
           student->score[3], student->score[4], student->score[5],
           student->score[6]);
}

// 打印班级信息
void printClass(Class *classes) {
    if (classes->head == NULL) {
        printf("班级无学生记录。\n");
        return;
    }
    printf("姓名\t学号\t高数\t英语\tC语言\t导论\t思政\t总分\t平均分\n");
    Student *current = classes->head;
    while (current) {
        printStudentInfo(current);
        current = current->next;
    }
}

// 按成绩查询
void searchScore(Class *classes, int courseIndex, double searchScore) {
    if (classes->head == NULL) {
        printf("班级无学生记录。\n");
        return;
    }
    printf("查询结果:\n");
    printf("%-10s %-12s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "姓名", "学号", "高数", "英语", "C语言", "导论", "思政", "总分", "平均分");

    Student *current = classes->head;
    int found = 0;
    while (current) {
        if (current->score[courseIndex] == searchScore) {
            printStudentInfo(current);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("无符合条件的学生。\n");
    }
}

// 按姓名查询
void searchName(Class *classes, char *name) {
    if (classes->head == NULL) {
        printf("班级无学生记录。\n");
        return;
    }

    Student *current = classes->head;
    int found = 0;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("找到学生:\n");
            printf("%-10s %-12s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
                   "姓名", "学号", "高数", "英语", "C语言", "导论", "思政", "总分", "平均分");
            printStudentInfo(current);
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("未找到学生 %s。\n", name);
    }
}

// 修改学生信息
void changeStudentInfo(Class *classes, char *studentId) {
    if (classes->head == NULL) {
        printf("班级无学生记录。\n");
        return;
    }

    Student *current = classes->head;
    int found = 0;

    while (current) {
        if (strcmp(current->studentId, studentId) == 0) {
            printf("找到学生 %s，输入新信息:\n", studentId);
            char name[10];
            char studentId[13];
            double score[5];

            printf("请输入姓名 学号: ");
            scanf("%s %s", name, studentId);
            printf("请输入5门课程成绩(高数、英语、C语言、导论、思政): ");
            for (int j = 0; j < 5; j++) {
                scanf("%lf", &score[j]);
            }

            strcpy(current->name, name);
            strcpy(current->studentId, studentId);

            double totalScore = 0;
            for (int i = 0; i < 5; i++) {
                current->score[i] = score[i];
                totalScore += score[i];
            }
            current->score[5] = totalScore;
            current->score[6] = totalScore / 5;

            printf("学生信息已更新。\n");
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("未找到学号为 %s 的学生。\n", studentId);
    }
}

// 删除学生
void deleteStudent(Class *classes, char *studentId) {
    if (classes->head == NULL) {
        printf("班级无学生记录。\n");
        return;
    }

    Student *current = classes->head;
    Student *prev = NULL;

    while (current) {
        if (strcmp(current->studentId, studentId) == 0) {
            if (prev == NULL) {
                classes->head = current->next;
            } else {
                prev->next = current->next;
            }

            if (current == classes->tail) {
                classes->tail = prev;
            }

            free(current);
            printf("学号为 %s 的学生已删除。\n", studentId);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("未找到学号为 %s 的学生。\n", studentId);
}

// 按成绩排序
void sortClassByScore(Class *classes, int courseIndex) {
    if (classes->head == NULL) {
        printf("班级无学生记录。\n");
        return;
    }

    for (Student *i = classes->head; i != NULL; i = i->next) {
        for (Student *j = i->next; j != NULL; j = j->next) {
            if (i->score[courseIndex] < j->score[courseIndex]) {
                swap(i, j);
            }
        }
    }
    printf("排序完成。\n");
}

// 交换学生信息
void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;

    // 保持链表结构不变
    Student *tempNext = a->next;
    a->next = b->next;
    b->next = tempNext;
}

// 插入学生
int insertStudent(Class *classes, char *name, char *studentId, double *score) {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("内存分配失败！\n");
        return 0;
    }

    strcpy(newStudent->name, name);
    strcpy(newStudent->studentId, studentId);

    double totalScore = 0;
    for (int i = 0; i < 5; i++) {
        newStudent->score[i] = score[i];
        totalScore += score[i];
    }
    newStudent->score[5] = totalScore;
    newStudent->score[6] = totalScore / 5;
    newStudent->next = NULL;

    // 插入到合适位置
    if (classes->head == NULL || newStudent->score[5] > classes->head->score[5]) {
        newStudent->next = classes->head;
        classes->head = newStudent;
        return 1;
    }

    Student *current = classes->head;
    while (current->next && newStudent->score[5] <= current->next->score[5]) {
        current = current->next;
    }

    newStudent->next = current->next;
    current->next = newStudent;

    if (newStudent->next == NULL) {
        classes->tail = newStudent;
    }
    return 1;
}

// 释放内存
void freeClassMemory(Class **classes, int classCount) {
    for (int i = 0; i < classCount; i++) {
        Student *current = classes[i]->head;
        while (current) {
            Student *temp = current;
            current = current->next;
            free(temp);
        }
        free(classes[i]);
    }
    free(classes);
}
