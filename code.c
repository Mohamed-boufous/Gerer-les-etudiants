#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    for(i=0; i<146; i++)
        printf("-");
    puisque dans chaque ligne dans les tableaux il y a 148 char, on a deux | alors on est besoin de 146 -
*/
//***********************************
typedef struct etudiant
{
    char nom[20];
    char prenom[20];
    char CNE[10];
    int notes[3];
    float moyenne;
} etudiant;
typedef struct node
{
    etudiant E;
    struct node *next;
} node;
//***********************************
node* inserttobeg(node *head,etudiant value)
{
    node *newnode=(node*)malloc(sizeof(node));
    newnode->E=value;
    newnode->next=head;
    head=newnode;
    return head;
}
//**********************************
node* delbeg(node *head)
{
    node *tmp=head;
    if(tmp==NULL)
    {
        printf("==> list vide!!\n");
        return head;
    }
    head=tmp->next;
    free(tmp);
    return head;
}
//***********************************
node* delend(node *head)
{
    node *tmp1=head;
    if(tmp1==NULL)
    {
        printf("==> list vide!!\n");
        return head;
    }
    if(tmp1->next==NULL)
    {
        head=NULL;
        free(tmp1);
        return head;
    }
    node *tmp2=tmp1->next;
    while(tmp2->next!=NULL)
    {
        tmp1=tmp1->next;
        tmp2=tmp2->next;
    }
    tmp1->next=NULL;
    free(tmp2);
    return head;
}
//***********************************
node* delpos(node *head,int pos)
{
    if(pos==1)
    {
        head=delbeg(head);
        return head;
    }
    int i;
    node *tmp1=head;
    node *tmp2=tmp1->next;
    for(i=1; i<pos-1; i++)
    {
        tmp1=tmp1->next;
        tmp2=tmp2->next;
    }

    tmp1->next=tmp2->next;
    free(tmp2);
    return head;
}
//***********************************
int listeEstTriee(node* head)
{
    if (head == NULL || head->next == NULL)
    {
        // la liste est vide ou contient un seul élément
        return 1;
    }
    node* tmp = head;
    while (tmp->next != NULL)
    {
        if (tmp->E.moyenne > tmp->next->E.moyenne)
            return 0;
        tmp = tmp->next;
    }
    return 1;
}
int JSEstTriee(node* head)
{
    if (head == NULL || head->next == NULL)
    {
        // la liste est vide ou contient un seul élément
        return 1;
    }
    node* tmp = head;
    while (tmp->next != NULL)
    {
        if (tmp->E.notes[0] > tmp->next->E.notes[0])
            return 0;
        tmp = tmp->next;
    }
    return 1;
}
int CSSEstTriee(node* head)
{
    if (head == NULL || head->next == NULL)
    {
        // la liste est vide ou contient un seul élément
        return 1;
    }
    node* tmp = head;
    while (tmp->next != NULL)
    {
        if (tmp->E.notes[1] > tmp->next->E.notes[1])
            return 0;
        tmp = tmp->next;
    }
    return 1;
}
int HTMLEstTriee(node* head)
{
    if (head == NULL || head->next == NULL)
    {
        // la liste est vide ou contient un seul élément
        return 1;
    }
    node* tmp = head;
    while (tmp->next != NULL)
    {
        if (tmp->E.notes[2] > tmp->next->E.notes[2])
            return 0;
        tmp = tmp->next;
    }
    return 1;
}
//***********************************
node* destroy(node *head)
{
    //deallouer la liste et la vider
    //si liste contient un ou aucun element
    if(head==NULL)
    {
        printf("==> list est vide!!\n");
        return head;
    }
    node *tmp1=head;
    if(tmp1->next==NULL)
    {
        head=NULL;
        free(tmp1);
        printf("==> la list est videe avec success!!\n");
        return head;
    }
    node *tmp2=tmp1->next;
    while(tmp2)
    {
        free(tmp1);
        tmp1=tmp2;
        tmp2=tmp2->next;
    }
    free(tmp1);
    head=NULL;
    printf("==> la list est videe avec success!!\n");
    return head;
}
//***********************************
void afficherListeEtudiants(node* head)
{
    node* tmp = head;
    if (tmp == NULL)
        printf("==> Il n'y a pas d'etudiants\n");
    else
    {
        printf("|Le nom              |Le prenom           |Le CNE              |JavaScript          |CSS                 |HTML                |Moyenne             |\n");
        int i;
        int occ=0;
        int js=0,css=0,html=0;
        float moy=0;
        float moyavg,jsavg,cssavg,htmlavg;
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        while (tmp != NULL)
        {
            printf("\n|%-20s|", tmp->E.nom);
            printf("%-20s|", tmp->E.prenom);
            printf("%-20s|", tmp->E.CNE);
            printf("%-20d|", tmp->E.notes[0]);
            printf("%-20d|", tmp->E.notes[1]);
            printf("%-20d|", tmp->E.notes[2]);
            printf("%-20.2f|", tmp->E.moyenne);
            js+=tmp->E.notes[0];
            css+=tmp->E.notes[1];
            html+=tmp->E.notes[2];
            moy+=tmp->E.moyenne;
            occ++;
            tmp = tmp->next;
        }
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        moyavg=(float)moy/occ;
        jsavg=(float)js/occ;
        cssavg=(float)css/occ;
        htmlavg=(float)html/occ;
        printf("\n\n---->> le nombre des etudiants: %d",occ);
        printf("\n---->> Moyenne de les moyennes: %.2f",moyavg);
        printf("\n---->> Moyenne des notes de JS: %.2f",jsavg);
        printf("\n---->> Moyenne des notes de CSS: %.2f",cssavg);
        printf("\n---->> Moyenne des notes de HTML: %.2f\n\n",htmlavg);
    }
}
//***********************************
node* etudiantAvecMaxMoyenne(node* head)
{
    int max = -1;
    //le max ne peut pas etre inferieur a 0
    node* tmp = head;
    node* b = NULL;
    if(tmp==NULL)
    {
        printf("==> list est vide!!\n");
        return NULL;
    }
    if(tmp->next==NULL)
    {
        //il y a un seul element
        return tmp;
    }
    while (tmp != NULL)
    {
        if (tmp->E.moyenne > max)
        {
            max = tmp->E.moyenne;
            b = tmp;
        }
        tmp = tmp->next;
    }
    return b;
}
node* suppE(node *head,char *CNE)
{
    if(head==NULL)
    {
        printf("==> List est vide!!\n");
        return head;
    }
    node *tmp=head;
    int n=1; // poue indiquer le position d'etudiant qu'in veut supprimer
    while(tmp)
    {
        if(strcmp(tmp->E.CNE,CNE)==0)
            break;
        tmp=tmp->next;
        n++;
    }
    if(tmp==NULL)
    {
        printf("l'etudiant n'est pas trouvee!!\n");
        return head;
    }
    if(tmp->next==NULL)
    {
        head=delend(head);
        return head;
    }
    if(n==1)
    {
        head=delbeg(head);
        //premier element
        return head;
    }
    head=delpos(head,n);
    return head;
}
//***********************************
void afficherEvalidee(node* head)
{
    node* tmp = head;
    int occ=0;
    int js=0,css=0,html=0;
    float moy=0;
    float moyavg,jsavg,cssavg,htmlavg;
    if (tmp == NULL)
        printf("==> Il n'y a pas d'etudiants\n");
    else
    {
        while(tmp!=NULL)
        {
            if(tmp->E.moyenne>=12)
                occ++;
            tmp=tmp->next;
        }
        if(occ==0)
        {
            printf("Il n y a pas des etudiants qui ont valide!!\n");
            return;
        }
        printf("|Le nom              |Le prenom           |Le CNE              |JavaScript          |CSS                 |HTML                |Moyenne             |\n");
        int i;
        tmp = head;
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        while (tmp != NULL)
        {
            if(tmp->E.moyenne>=12)
            {
                printf("\n|%-20s|", tmp->E.nom);
                printf("%-20s|", tmp->E.prenom);
                printf("%-20s|", tmp->E.CNE);
                printf("%-20d|", tmp->E.notes[0]);
                printf("%-20d|", tmp->E.notes[1]);
                printf("%-20d|", tmp->E.notes[2]);
                printf("%-20.2f|", tmp->E.moyenne);
                js+=tmp->E.notes[0];
                css+=tmp->E.notes[1];
                html+=tmp->E.notes[2];
                moy+=tmp->E.moyenne;
            }
            tmp = tmp->next;
        }
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        moyavg=(float)moy/occ;
        jsavg=(float)js/occ;
        cssavg=(float)css/occ;
        htmlavg=(float)html/occ;
        if(occ==1)
            printf("\n\n---->> Il y a un etudiant qui a valide\n\n");
        else
            printf("\n\n---->> Il y a %d des etudiants qui ont valide\n\n",occ);
        printf("\n---->> Moyenne de les moyennes: %.2f",moyavg);
        printf("\n---->> Moyenne des notes de JS: %.2f",jsavg);
        printf("\n---->> Moyenne des notes de CSS: %.2f",cssavg);
        printf("\n---->> Moyenne des notes de HTML: %.2f\n\n",htmlavg);
    }
}
//***********************************
void afficherEvalideeJS(node* head)
{
    node* tmp = head;
    int occ=0;
    int js=0,css=0,html=0;
    float moy=0;
    float moyavg,jsavg,cssavg,htmlavg;
    if (tmp == NULL)
        printf("==> Il n'y a pas d'etudiants\n");
    else
    {
        while(tmp!=NULL)
        {
            if(tmp->E.notes[0]>=12)
                occ++;
            tmp=tmp->next;
        }
        if(occ==0)
        {
            printf("Il n y a pas des etudiants qui ont valide JavaScript!!\n");
            return;
        }
        printf("|Le nom              |Le prenom           |Le CNE              |JavaScript          |CSS                 |HTML                |Moyenne             |\n");
        int i;
        tmp = head;
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        while (tmp != NULL)
        {
            if(tmp->E.notes[0]>=12)
            {
                printf("\n|%-20s|", tmp->E.nom);
                printf("%-20s|", tmp->E.prenom);
                printf("%-20s|", tmp->E.CNE);
                printf("%-20d|", tmp->E.notes[0]);
                printf("%-20d|", tmp->E.notes[1]);
                printf("%-20d|", tmp->E.notes[2]);
                printf("%-20.2f|", tmp->E.moyenne);
                js+=tmp->E.notes[0];
                css+=tmp->E.notes[1];
                html+=tmp->E.notes[2];
                moy+=tmp->E.moyenne;
            }
            tmp = tmp->next;
        }
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        moyavg=(float)moy/occ;
        jsavg=(float)js/occ;
        cssavg=(float)css/occ;
        htmlavg=(float)html/occ;
        if(occ==1)
            printf("\n\n---->> Il y a un etudiant qui a valide JS\n\n");
        else
            printf("\n\n---->> Il y a %d des etudiants qui ont valide JS\n\n",occ);
        printf("\n---->> Moyenne de les moyennes: %.2f",moyavg);
        printf("\n---->> Moyenne des notes de JS: %.2f",jsavg);
        printf("\n---->> Moyenne des notes de CSS: %.2f",cssavg);
        printf("\n---->> Moyenne des notes de HTML: %.2f\n\n",htmlavg);
    }
}
//***********************************
void afficherEvalideeCSS(node* head)
{
    node* tmp = head;
    int occ=0;
    int js=0,css=0,html=0;
    float moy=0;
    float moyavg,jsavg,cssavg,htmlavg;
    if (tmp == NULL)
        printf("==> Il n'y a pas d'etudiants\n");
    else
    {
        while(tmp!=NULL)
        {
            if(tmp->E.notes[1]>=12)
                occ++;
            tmp=tmp->next;
        }
        if(occ==0)
        {
            printf("Il n y a pas des etudiants qui ont valide CSS!!\n");
            return;
        }
        printf("|Le nom              |Le prenom           |Le CNE              |JavaScript          |CSS                 |HTML                |Moyenne             |\n");
        int i;
        tmp = head;
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        while (tmp != NULL)
        {
            if(tmp->E.notes[1]>=12)
            {
                printf("\n|%-20s|", tmp->E.nom);
                printf("%-20s|", tmp->E.prenom);
                printf("%-20s|", tmp->E.CNE);
                printf("%-20d|", tmp->E.notes[0]);
                printf("%-20d|", tmp->E.notes[1]);
                printf("%-20d|", tmp->E.notes[2]);
                printf("%-20.2f|", tmp->E.moyenne);
                js+=tmp->E.notes[0];
                css+=tmp->E.notes[1];
                html+=tmp->E.notes[2];
                moy+=tmp->E.moyenne;
            }
            tmp = tmp->next;
        }
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        moyavg=(float)moy/occ;
        jsavg=(float)js/occ;
        cssavg=(float)css/occ;
        htmlavg=(float)html/occ;
        if(occ==1)
            printf("\n\n---->> Il y a un etudiant qui a valide CSS\n\n");
        else
            printf("\n\n---->> Il y a %d des etudiants qui ont valide CSS\n\n",occ);
        printf("\n---->> Moyenne de les moyennes: %.2f",moyavg);
        printf("\n---->> Moyenne des notes de JS: %.2f",jsavg);
        printf("\n---->> Moyenne des notes de CSS: %.2f",cssavg);
        printf("\n---->> Moyenne des notes de HTML: %.2f\n\n",htmlavg);
    }
}
//***********************************
void afficherEvalideeHTML(node* head)
{
    node* tmp = head;
    int occ=0;
    int js=0,css=0,html=0;
    float moy=0;
    float moyavg,jsavg,cssavg,htmlavg;
    if (tmp == NULL)
        printf("==> Il n'y a pas d'etudiants\n");
    else
    {
        while(tmp!=NULL)
        {
            if(tmp->E.notes[2]>=12)
                occ++;
            tmp=tmp->next;
        }
        if(occ==0)
        {
            printf("Il n y a pas des etudiants qui ont valide HTML!!\n");
            return;
        }
        printf("|Le nom              |Le prenom           |Le CNE              |JavaScript          |CSS                 |HTML                |Moyenne             |\n");
        int i;
        tmp = head;
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        while (tmp != NULL)
        {
            if(tmp->E.notes[2]>=12)
            {
                printf("\n|%-20s|", tmp->E.nom);
                printf("%-20s|", tmp->E.prenom);
                printf("%-20s|", tmp->E.CNE);
                printf("%-20d|", tmp->E.notes[0]);
                printf("%-20d|", tmp->E.notes[1]);
                printf("%-20d|", tmp->E.notes[2]);
                printf("%-20.2f|", tmp->E.moyenne);
                js+=tmp->E.notes[0];
                css+=tmp->E.notes[1];
                html+=tmp->E.notes[2];
                moy+=tmp->E.moyenne;
            }
            tmp = tmp->next;
        }
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        moyavg=(float)moy/occ;
        jsavg=(float)js/occ;
        cssavg=(float)css/occ;
        htmlavg=(float)html/occ;
        if(occ==1)
            printf("\n\n---->> Il y a un etudiant qui a valide HTML\n\n");
        else
            printf("\n\n---->> Il y a %d des etudiants qui ont valide HTML\n\n",occ);
        printf("\n---->> Moyenne de les moyennes: %.2f",moyavg);
        printf("\n---->> Moyenne des notes de JS: %.2f",jsavg);
        printf("\n---->> Moyenne des notes de CSS: %.2f",cssavg);
        printf("\n---->> Moyenne des notes de HTML: %.2f\n\n",htmlavg);
    }
}
//***********************************
void afficherEpasvalidee(node* head)
{
    node* tmp = head;
    int occ=0;
    int js=0,css=0,html=0;
    float moy=0;
    float moyavg,jsavg,cssavg,htmlavg;
    if (tmp == NULL)
        printf("==> Il n'y a pas d'etudiants\n");
    else
    {
        while(tmp!=NULL)
        {
            if(tmp->E.moyenne<12)
                occ++;
            tmp=tmp->next;
        }
        if(occ==0)
        {
            printf("tous les etudiants ont valide!!\n");
            return;
        }
        printf("|Le nom              |Le prenom           |Le CNE              |JavaScript          |CSS                 |HTML                |Moyenne             |\n");
        int i;
        tmp = head;
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        while (tmp != NULL)
        {
            if(tmp->E.moyenne<12)
            {
                printf("\n|%-20s|", tmp->E.nom);
                printf("%-20s|", tmp->E.prenom);
                printf("%-20s|", tmp->E.CNE);
                printf("%-20d|", tmp->E.notes[0]);
                printf("%-20d|", tmp->E.notes[1]);
                printf("%-20d|", tmp->E.notes[2]);
                printf("%-20.2f|", tmp->E.moyenne);
                js+=tmp->E.notes[0];
                css+=tmp->E.notes[1];
                html+=tmp->E.notes[2];
                moy+=tmp->E.moyenne;
            }
            tmp = tmp->next;
        }
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        moyavg=(float)moy/occ;
        jsavg=(float)js/occ;
        cssavg=(float)css/occ;
        htmlavg=(float)html/occ;
        if(occ==1)
            printf("\n\n---->> Il y a un etudiant qui n'a pas valide\n\n");
        else
            printf("\n\n---->> Il y a %d des etudiants qui n'ont pas valide\n\n",occ);
        printf("\n---->> Moyenne de les moyennes: %.2f",moyavg);
        printf("\n---->> Moyenne des notes de JS: %.2f",jsavg);
        printf("\n---->> Moyenne des notes de CSS: %.2f",cssavg);
        printf("\n---->> Moyenne des notes de HTML: %.2f\n\n",htmlavg);
    }
}
//***********************************
void afficherEpasvalideeJS(node* head)
{
    node* tmp = head;
    int occ=0;
    int js=0,css=0,html=0;
    float moy=0;
    float moyavg,jsavg,cssavg,htmlavg;
    if (tmp == NULL)
        printf("==> Il n'y a pas d'etudiants\n");
    else
    {
        while(tmp!=NULL)
        {
            if(tmp->E.notes[0]<12)
                occ++;
            tmp=tmp->next;
        }
        if(occ==0)
        {
            printf("tous les etudiants ont valide JavaScript!!\n");
            return;
        }
        printf("|Le nom              |Le prenom           |Le CNE              |JavaScript          |CSS                 |HTML                |Moyenne             |\n");
        int i;
        tmp = head;
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        while (tmp != NULL)
        {
            if(tmp->E.notes[0]<12)
            {
                printf("\n|%-20s|", tmp->E.nom);
                printf("%-20s|", tmp->E.prenom);
                printf("%-20s|", tmp->E.CNE);
                printf("%-20d|", tmp->E.notes[0]);
                printf("%-20d|", tmp->E.notes[1]);
                printf("%-20d|", tmp->E.notes[2]);
                printf("%-20.2f|", tmp->E.moyenne);
                js+=tmp->E.notes[0];
                css+=tmp->E.notes[1];
                html+=tmp->E.notes[2];
                moy+=tmp->E.moyenne;
            }
            tmp = tmp->next;
        }
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        moyavg=(float)moy/occ;
        jsavg=(float)js/occ;
        cssavg=(float)css/occ;
        htmlavg=(float)html/occ;
        if(occ==1)
            printf("\n\n---->> Il y a un etudiant qui n'a pas valide JS\n\n");
        else
            printf("\n\n---->> Il y a %d des etudiants qui n'ont pas valide JS\n\n",occ);
        printf("\n---->> Moyenne de les moyennes: %.2f",moyavg);
        printf("\n---->> Moyenne des notes de JS: %.2f",jsavg);
        printf("\n---->> Moyenne des notes de CSS: %.2f",cssavg);
        printf("\n---->> Moyenne des notes de HTML: %.2f\n\n",htmlavg);
    }
}
//***********************************
void afficherEpasvalideeCSS(node* head)
{
    node* tmp = head;
    int occ=0;
    int js=0,css=0,html=0;
    float moy=0;
    float moyavg,jsavg,cssavg,htmlavg;
    if (tmp == NULL)
        printf("==> Il n'y a pas d'etudiants\n");
    else
    {
        while(tmp!=NULL)
        {
            if(tmp->E.notes[1]<12)
                occ++;
            tmp=tmp->next;
        }
        if(occ==0)
        {
            printf("tous les etudiants ont valide CSS!!\n");
            return;
        }
        printf("|Le nom              |Le prenom           |Le CNE              |JavaScript          |CSS                 |HTML                |Moyenne             |\n");
        int i;
        tmp = head;
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        while (tmp != NULL)
        {
            if(tmp->E.notes[1]<12)
            {
                printf("\n|%-20s|", tmp->E.nom);
                printf("%-20s|", tmp->E.prenom);
                printf("%-20s|", tmp->E.CNE);
                printf("%-20d|", tmp->E.notes[0]);
                printf("%-20d|", tmp->E.notes[1]);
                printf("%-20d|", tmp->E.notes[2]);
                printf("%-20.2f|", tmp->E.moyenne);
                js+=tmp->E.notes[0];
                css+=tmp->E.notes[1];
                html+=tmp->E.notes[2];
                moy+=tmp->E.moyenne;
            }
            tmp = tmp->next;
        }
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        moyavg=(float)moy/occ;
        jsavg=(float)js/occ;
        cssavg=(float)css/occ;
        htmlavg=(float)html/occ;
        if(occ==1)
            printf("\n\n---->> Il y a un etudiant qui n'a pas valide CSS\n\n");
        else
            printf("\n\n---->> Il y a %d des etudiants qui n'ont pas valide CSS\n\n",occ);
        printf("\n---->> Moyenne de les moyennes: %.2f",moyavg);
        printf("\n---->> Moyenne des notes de JS: %.2f",jsavg);
        printf("\n---->> Moyenne des notes de CSS: %.2f",cssavg);
        printf("\n---->> Moyenne des notes de HTML: %.2f\n\n",htmlavg);
    }
}
//***********************************
void afficherEpasvalideeHTML(node* head)
{
    node* tmp = head;
    int occ=0;
    int js=0,css=0,html=0;
    float moy=0;
    float moyavg,jsavg,cssavg,htmlavg;
    if (tmp == NULL)
        printf("==> Il n'y a pas d'etudiants\n");
    else
    {
        while(tmp!=NULL)
        {
            if(tmp->E.notes[2]<12)
                occ++;
            tmp=tmp->next;
        }
        if(occ==0)
        {
            printf("tous les etudiants ont valide HTML!!\n");
            return;
        }
        printf("|Le nom              |Le prenom           |Le CNE              |JavaScript          |CSS                 |HTML                |Moyenne             |\n");
        int i;
        tmp = head;
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        while (tmp != NULL)
        {
            if(tmp->E.notes[2]<12)
            {
                printf("\n|%-20s|", tmp->E.nom);
                printf("%-20s|", tmp->E.prenom);
                printf("%-20s|", tmp->E.CNE);
                printf("%-20d|", tmp->E.notes[0]);
                printf("%-20d|", tmp->E.notes[1]);
                printf("%-20d|", tmp->E.notes[2]);
                printf("%-20.2f|", tmp->E.moyenne);
                js+=tmp->E.notes[0];
                css+=tmp->E.notes[1];
                html+=tmp->E.notes[2];
                moy+=tmp->E.moyenne;
            }
            tmp = tmp->next;
        }
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        moyavg=(float)moy/occ;
        jsavg=(float)js/occ;
        cssavg=(float)css/occ;
        htmlavg=(float)html/occ;
        if(occ==1)
            printf("\n\n---->> Il y a un etudiant qui n'a pas valide HTML\n\n");
        else
            printf("\n\n---->> Il y a %d des etudiants qui n'ont pas valide HTML\n\n",occ);
        printf("\n---->> Moyenne de les moyennes: %.2f",moyavg);
        printf("\n---->> Moyenne des notes de JS: %.2f",jsavg);
        printf("\n---->> Moyenne des notes de CSS: %.2f",cssavg);
        printf("\n---->> Moyenne des notes de HTML: %.2f\n\n",htmlavg);
    }
}
node* chercherE(node *head,char *rnom,char *rprenom)
{
    node *tmp=head;
    if(tmp==NULL)
    {
        printf("==> list est vide!!\n");
        return NULL;
    }
    while(tmp)
    {
        if(strcmp (rnom, tmp->E.nom)==0&&strcmp (rprenom, tmp->E.prenom)==0)
            return tmp;
        tmp=tmp->next;
    }
    printf("l'etudiant n'est pas trouvee!!\n");
    return NULL;
}
//***********************************
void misAjour(node *Emisajour)
{
    int choix;
    do
    {
        printf("\n\n");
        printf("  |-----------------------------------------------------|\n");
        printf("  |                     mis a jour:                     |\n");
        printf("  |            %-20s %-20s|\n",Emisajour->E.nom,Emisajour->E.prenom);
        printf("  |-----------------------------------------------------|\n");
        printf("  | 1. Nom                                              |\n");
        printf("  | 2. Prenom                                           |\n");
        printf("  | 3. Note de JavaScript                               |\n");
        printf("  | 4. Note de CSS                                      |\n");
        printf("  | 5. Note de HTML                                     |\n");
        printf("  | 0. Rien                                             |\n");
        printf("  |-----------------------------------------------------|\n");
        printf("Entrer votre choix : ");
        scanf("%d", &choix);
        switch(choix)
        {
        case 0:
            break;
        case 1:
            getchar();
            printf("Entrer le nom : ");
            gets(Emisajour->E.nom);
            break;
        case 2:
            getchar();
            printf("Entrer le prenom : ");
            gets(Emisajour->E.prenom);
            break;
        case 3:
            printf("Entrer la note de JavaScript : ");
            scanf("%d", &Emisajour->E.notes[0]);
            while(Emisajour->E.notes[0]<0||Emisajour->E.notes[0]>20)
            {
                printf("Entrer une note >=0 et <=20: ");
                scanf("%d", &Emisajour->E.notes[0]);
            }
            break;
        case 4:
            printf("Entrer la note de CSS : ");
            scanf("%d", &Emisajour->E.notes[1]);
            while(Emisajour->E.notes[1]<0||Emisajour->E.notes[1]>20)
            {
                printf("Entrer une note >=0 et <=20: ");
                scanf("%d", &Emisajour->E.notes[1]);
            }
            break;
        case 5:
            printf("Entrer la note de HTML : ");
            scanf("%d", &Emisajour->E.notes[2]);
            while(Emisajour->E.notes[2]<0||Emisajour->E.notes[2]>20)
            {
                printf("Entrer une note >=0 et <=20: ");
                scanf("%d", &Emisajour->E.notes[2]);
            }
            break;
        default:
            printf("Choix invalide !\n");
            break;
        }
    }
    while (choix != 0);
    Emisajour->E.moyenne=(Emisajour->E.notes[0] + Emisajour->E.notes[1] + Emisajour->E.notes[2]) / 3.0;
}
//***********************************
etudiant init(FILE *fp)
{
    etudiant E;
    char *Ph=(char*)malloc(100);
    if (Ph == NULL)
    {
        printf("Erreur d'allocation de memoire\n");
        exit(44);
    }
    fgets(Ph,100,fp);
    sscanf(Ph,"%[^:]:%[^:]:%[^:]:%d:%d:%d",E.CNE,E.prenom,E.nom,&E.notes[0],&E.notes[1],&E.notes[2]);
    return E;
}
void save(node *head,FILE *ofp)
{
    if(head==NULL){
        printf("List est vide!!\n");
        return;
    }
    node *tmp=head;
    while(tmp)
    {
        fprintf(ofp,"%s:%s:%s:%d:%d:%d\n",tmp->E.CNE,tmp->E.prenom,tmp->E.nom,tmp->E.notes[0],tmp->E.notes[1],tmp->E.notes[2]);
        tmp=tmp->next;
    }
}
//**********************************
node* triMoyen(node* head)
{
    if(listeEstTriee(head))
    {
        printf("List est deja triee selon le moyenne!!\n");
        return head;
    }
    int swapped ;
    node *ptr1,*lptr;
    etudiant tmp;
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    ptr1= head, lptr = NULL;
    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->E.moyenne > ptr1->next->E.moyenne)
            {
                tmp = ptr1->E;
                ptr1->E = ptr1->next->E;
                ptr1->next->E = tmp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
    return head;
}
node * triJS( node *head)
{
    if(JSEstTriee(head))
    {
        printf("List est deja triee selon la note de JavaScript!!\n");
        return head;
    }
    int swapped ;
    node *ptr1,*lptr;
    etudiant tmp;
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    ptr1= head, lptr = NULL;
    do
    {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr)
        {
            if (ptr1->E.notes[0] > ptr1->next->E.notes[0])
            {
                tmp = ptr1->E;
                ptr1->E = ptr1->next->E;
                ptr1->next->E = tmp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
    return head;
}
node * triCSS( node *head)
{
    if(CSSEstTriee(head))
    {
        printf("List est deja triee selon la note de CSS!!\n");
        return head;
    }
    int swapped ;
    node *ptr1,*lptr;
    etudiant tmp;
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    ptr1= head, lptr = NULL;
    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->E.notes[1] > ptr1->next->E.notes[1])
            {
                tmp = ptr1->E;
                ptr1->E = ptr1->next->E;
                ptr1->next->E = tmp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);

    return head;
}
node * triHTML( node *head)
{
    if(HTMLEstTriee(head))
    {
        printf("List est deja triee selon la note de HTML!!\n");
        return head;
    }
    int swapped ;
    node *ptr1,*lptr;
    etudiant tmp;
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    ptr1= head, lptr = NULL;
    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->E.notes[2] > ptr1->next->E.notes[2])
            {
                tmp = ptr1->E;
                ptr1->E = ptr1->next->E;
                ptr1->next->E = tmp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
    return head;
}
//***********************************
void afficherAvecMoyenne(node *head,int val)
{
    node *tmp=head;
    int occ=0; //au cas il n y a pas des etudiants
    if (tmp == NULL)
        printf("==> Il n'y a pas d'etudiants\n");
    else
    {
        while(tmp!=NULL)
        {
            if(tmp->E.moyenne>=val&&tmp->E.moyenne<val+1)
            {
                occ++;
                break;
            }
            tmp=tmp->next;
        }
        if(occ==0)
        {
            printf("Il n y a pas des etudiants qui ont obtenu ce moyen!!\n");
            return;
        }
        printf("|Le nom              |Le prenom           |Le CNE              |JavaScript          |CSS                 |HTML                |Moyenne             |\n");
        int i;
        tmp = head;
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
        while(tmp!=NULL)
        {
            if(tmp->E.moyenne>=val&&tmp->E.moyenne<val+1)
            {
                printf("\n|%-20s|", tmp->E.nom);
                printf("%-20s|", tmp->E.prenom);
                printf("%-20s|", tmp->E.CNE);
                printf("%-20d|", tmp->E.notes[0]);
                printf("%-20d|", tmp->E.notes[1]);
                printf("%-20d|", tmp->E.notes[2]);
                printf("%-20.2f|", tmp->E.moyenne);
            }
            tmp=tmp->next;
        }
        printf("\n|");
        for(i=0; i<146; i++)
            printf("-");
        printf("|\n");
    }
}
//***********************************
node* insereMoyenne(node* head)
{
    if(!listeEstTriee(head))
    {
        char choix;
        printf("List n'est pas triee par moyenne!!\n");
        printf("Trier la list?? (o/n): ");
        scanf(" %c",&choix);
        if(choix=='o')
            head=triMoyen(head);
        else
            return head;
    }
    node *b = (node*)malloc(sizeof(node));
    b->next = NULL;
    getchar();
    printf("Entrer le nom : ");
    gets(b->E.nom);
    printf("Entrer le prenom : ");
    gets(b->E.prenom);
    printf("Entrer le cne : ");
    gets(b->E.CNE);
    printf("Entrer la note de JavaScript : ");
    scanf("%d", &b->E.notes[0]);
    while(b->E.notes[0]<0||b->E.notes[0]>20)
    {
        printf("Entrer une note >=0 et <=20: ");
        scanf("%d", &b->E.notes[0]);
    }
    printf("Entrer la note de HTML : ");
    scanf("%d", &b->E.notes[1]);
    while(b->E.notes[1]<0||b->E.notes[1]>20)
    {
        printf("Entrer une note >=0 et <=20: ");
        scanf("%d", &b->E.notes[1]);
    }
    printf("Entrer la note de CSS : ");
    scanf("%d", &b->E.notes[2]);
    while(b->E.notes[2]<0||b->E.notes[2]>20)
    {
        printf("Entrer une note >=0 et <=20: ");
        scanf("%d", &b->E.notes[2]);
    }
    b->E.moyenne = (b->E.notes[0] + b->E.notes[1] + b->E.notes[2]) / 3.0;

    if (head == NULL)
    {
        head = b;
    }
    else
    {
        node *tmp = head;
        if (head->E.moyenne >= b->E.moyenne)
        {
            b->next = head;
            head = b;
        }
        else
        {
            while (tmp->next != NULL && tmp->next->E.moyenne < b->E.moyenne)
            {
                tmp = tmp->next;
            }
            if (tmp->next != NULL)
            {
                b->next = tmp->next;
            }
            tmp->next = b;
        }
    }
    return head;
}

//***********************************
int main()
{
    node *head = NULL; //premier elem de liste chaine
    node *EtudiantAchercher; //on stock l'etudiant qu'on recherche
    node *max; //etudiant avec max note
    etudiant ajt; //etudiant qu'on ajout
    int choix1,choix2; //menu principale et secondaire
    char rnom[20],rprenom[20]; //on l'utilise pour cherecher un etudiant par nom et prenom
    char CNE[10]; //on l'utilise pour cherecher un etudiant par CNE
    int m; //on l'utilise pour afficher les etudiant ayant un moyen
    FILE *fp,*ofp;
    //fp: first file pointer, ofp:open new file pointer
    if((fp=fopen("students.txt","rt"))==NULL) //ouvrir fichier en mode r
    {
        printf("Erreur de lecture!!\n");
        exit(44);
    }
    if((ofp=fopen("nouveau list.txt","wt"))==NULL) //creer un nouveau fichier en mode w pour le mis a jour chaque fois
    {
        printf("Erreur!!\n");
        exit(44);
    }
    do
    {
        printf("\n\n");
        printf("  |-----------------------------------------------------|\n");
        printf("  |                Menu principal                       |\n");
        printf("  |-----------------------------------------------------|\n");
        printf("  | 1. Afficher la liste des etudiants                  |\n");
        printf("  | 2. Importer les etudiants du fichier                |\n");
        printf("  | 3. Ajouter un nouvel etudiant                       |\n");
        printf("  | 4. Suprimmer tous les etudiants                     |\n");
        printf("  | 5. Autres operations                                |\n");
        printf("  | 6. enregistrer                                      |\n");
        printf("  | 0. Quitter                                          |\n");
        printf("  |-----------------------------------------------------|\n");
        printf("Entrer votre choix : ");
        scanf("%d", &choix1);

        switch (choix1)
        {
        case 0:
            printf("****Au revoir :) ****\n");
            break;
        case 1:
            printf("Affichage de la liste des etudiants :\n");
            afficherListeEtudiants(head);
            break;
        case 2:
            if(feof(fp))
            {
                printf("==> Les etudiants sont deja importes!!\n");
                break;
            }
            while(!feof(fp))
            {
                ajt=init(fp);
                ajt.moyenne=(ajt.notes[0] + ajt.notes[1] + ajt.notes[2]) / 3.0;
                head = inserttobeg(head, ajt);
                //recuperer un ligne qui contien information sur un etudiant d'apres le fichier et le transformer avec init et on l'insere au debut de list
            }
            break;
        case 3:
            getchar();
            printf("Entrer le nom : ");
            gets(ajt.nom);
            printf("Entrer le prenom : ");
            gets(ajt.prenom);
            printf("Entrer le cne : ");
            gets(ajt.CNE);
            printf("Entrer la note de JavaScript : ");
            scanf("%d", &ajt.notes[0]);
            while(ajt.notes[0]<0||ajt.notes[0]>20)
            {
                printf("Entrer une note >=0 et <=20: ");
                scanf("%d", &ajt.notes[0]);
            }
            printf("Entrer la note de HTML : ");
            scanf("%d", &ajt.notes[1]);
            while(ajt.notes[1]<0||ajt.notes[1]>20)
            {
                printf("Entrer une note >=0 et <=20: ");
                scanf("%d", &ajt.notes[1]);
            }
            printf("Entrer la note de CSS : ");
            scanf("%d", &ajt.notes[2]);
            while(ajt.notes[2]<0||ajt.notes[2]>20)
            {
                printf("Entrer une note >=0 et <=20: ");
                scanf("%d", &ajt.notes[2]);
            }
            ajt.moyenne=(ajt.notes[0] + ajt.notes[1] + ajt.notes[2]) / 3.0;
            head = inserttobeg(head, ajt);
            break;
        case 4:
            head=destroy(head);
            rewind(fp); //au cas on a supprimer tous les etudiant on peut les importer de fichier une autre fois
            break;
        case 5:
            do
            {
                system("cls");
                printf("\n\n");
                printf("  |-----------------------------------------------------|\n");
                printf("  |                Menu Secondaire                      |\n");
                printf("  |-----------------------------------------------------|\n");
                printf("  | 1.  Trier les etudiants par moyenne                 |\n");
                printf("  | 2.  Trier les etudiants par note de JavaScript      |\n");
                printf("  | 3.  Trier les etudiants par note de CSS             |\n");
                printf("  | 4.  Trier les etudiants par note de HTLM            |\n");
                printf("  | 5.  suprimer un etudiant                            |\n");
                printf("  | 6.  Les etudiants valide le module                  |\n");
                printf("  | 7.  Les etudiants valide JavaScript                 |\n");
                printf("  | 8.  Les etudiants valide CSS                        |\n");
                printf("  | 9.  Les etudiants valide HTML                       |\n");
                printf("  | 10. Les etudiants non valide                        |\n");
                printf("  | 11. Les etudiants non valide JavaScript             |\n");
                printf("  | 12. Les etudiants non valide CSS                    |\n");
                printf("  | 13. Les etudiants non valide HTML                   |\n");
                printf("  | 14. Chercher un etudiant                            |\n");
                printf("  | 15. afficher selon moyenne                          |\n");
                printf("  | 16. insere et reste triee (selon moyenne)           |\n");
                printf("  | 17. afficher l'etudiant avec le max moyenne         |\n");
                printf("  | 0.  Revenir au menu precedant                       |\n");
                printf("  |-----------------------------------------------------|\n");
                printf("Entrer votre choix : ");
                scanf("%d", &choix2);
                switch(choix2)
                {
                case 0:
                    break;
                case 1:
                    printf("Tri par moyenne:\n");
                    head=triMoyen(head);
                    afficherListeEtudiants(head);
                    break;
                case 2:
                    printf("Tri par note de JavaScript:\n");
                    head=triJS(head);
                    afficherListeEtudiants(head);
                    break;
                case 3:
                    printf("Tri par note de CSS:\n");
                    head=triCSS(head);
                    afficherListeEtudiants(head);
                    break;
                case 4:
                    printf("Tri par note de HTML:\n");
                    head=triHTML(head);
                    afficherListeEtudiants(head);
                    break;
                case 5:
                    getchar();
                    printf("Entrer CNE: \n");
                    gets(CNE);
                    head=suppE(head,CNE); //cette fonction supprime un etudiant a l'aide des autre fonctions(delbeg, delend et delpos)
                    afficherListeEtudiants(head);
                    break;
                case 6:
                    printf("Les etudiants qui ont valide le module:\n");
                    afficherEvalidee(head);
                    break;
                case 7:
                    printf("Les etudiants qui ont valide JavaScript:\n");
                    afficherEvalideeJS(head);
                    break;
                case 8:
                    printf("Les etudiants qui ont valide CSS:\n");
                    afficherEvalideeCSS(head);
                    break;
                case 9:
                    printf("Les etudiants qui ont valide HTML:\n");
                    afficherEvalideeHTML(head);
                    break;
                case 10:
                    printf("Les etudiants qui n'ont pas valide le module:\n");
                    afficherEpasvalidee(head);
                    break;
                case 11:
                    printf("Les etudiants qui n'ont pas valide JavaScript:\n");
                    afficherEpasvalideeJS(head);
                    break;
                case 12:
                    printf("Les etudiants qui n'ont pas valide CSS:\n");
                    afficherEpasvalideeCSS(head);
                    break;
                case 13:
                    printf("Les etudiants qui n'ont pas valide HTML:\n");
                    afficherEpasvalideeHTML(head);
                    break;
                case 14:
                    getchar();
                    printf("chercher un etudiants:\n");
                    printf("Entrer le nom:\n");
                    gets(rnom);
                    printf("Entrer le prenom:\n");
                    gets(rprenom);
                    EtudiantAchercher=chercherE(head,rnom,rprenom);
                    if(EtudiantAchercher!=NULL)
                    {
                        printf("l'etudiant %s %s %s est trouvee a l'adresse %p\n",EtudiantAchercher->E.CNE,EtudiantAchercher->E.nom,EtudiantAchercher->E.prenom,EtudiantAchercher);
                        misAjour(EtudiantAchercher);
                    }
                    break;
                case 15:
                    printf("Entrer le moyen:\n");
                    scanf("%d",&m);
                    afficherAvecMoyenne(head,m); //on affiche selon un intervalle
                    break;
                case 16:
                    printf("insere et reste triee (selon moyen):\n");
                    head=insereMoyenne(head);
                    afficherListeEtudiants(head);
                    break;
                case 17:
                    printf("etudiant avec max moyenne:\n");
                    max=etudiantAvecMaxMoyenne(head);
                    if(max!=NULL)
                    {
                        printf("l'etudiant %s %s avec le moyenne %.2f est le majorant\n",max->E.nom,max->E.prenom,max->E.moyenne);
                        misAjour(max);
                    }
                    else
                    {
                        printf("erreur!!\n");
                    }
                    break;
                default:
                    printf("Choix invalide !\n");
                    break;
                }
                printf("\n\n****Appuyer pour continuer****");
                system("pause>NULL");
            }
            while(choix2!=0);
            break;
        case 6:
            save(head,ofp); //ajouter les etudiants dans un nouveau fichier
            break;
        default:
            printf("Choix invalide !\n");
            break;
        }
    }
    while (choix1 != 0);
    fclose(fp);
    fclose(ofp);
    destroy(head);
    return 0;
}
