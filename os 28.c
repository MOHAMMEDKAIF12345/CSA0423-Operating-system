    #include<stdio.h>

    #include<dirent.h>

    int main() {

        char fn[10], pat[10], temp[200];

        FILE *fp;

        printf("\n Enter file name : ");

        scanf("%s", fn);

        printf("Enter the pattern: ");

        scanf("%s", pat);

        fp = fopen(fn, "r");

        while (!feof(fp)) {

            fgets(temp, sizeof(fp), fp);

            if (strcmp(temp, pat))

                printf("%s", temp);

        }

        fclose(fp);

        return 1;

    }
