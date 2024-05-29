#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "social.h"

#define ll long long
#define FOR(i,a,b) for(int i=a; i<b; i++)

ll ID=0;
network* sn1;

long long uniqueID()
{
    return ID++;
}

date getDate()
{
    date d;
    printf("Enter day of the month\n");
    while (scanf("%d", &d.day) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }
    printf("Enter month\n");
    while (scanf("%d", &d.month) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }
    printf("Enter year\n");
    while (scanf("%d", &d.year) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }

    return d;
}

coord2D getCoord2D()
{
    coord2D loc;
    printf("Enter X coordinate\n");
    while (scanf("%f", &loc.x) != 1) {
        printf("Invalid input. Please enter a valid floating point number.\n\n");
        clearInputBuffer();
    }
    printf("Enter Y coordinate\n");
    while (scanf("%f", &loc.y) != 1) {
        printf("Invalid input. Please enter a valid floating point number.\n\n");
        clearInputBuffer();
    }
    return loc;
}

int datecmp(date d1, date d2)
{
    if (d1.year < d2.year) return -1;
    else if (d1.year > d2.year) return 1;
    else if (d1.month < d2.month) return -1;
    else if (d1.month > d2.month) return 1;
    else if (d1.day < d2.day) return -1;
    else if (d1.day > d2.day) return 1;
    else return 0;
}

void printDate(date d)
{
    printf("%d.%d.%d\n", d.day, d.month, d.year);
}

void clearInputBuffer() {
    int c;
    // Read characters from the input buffer until a newline character or EOF is encountered
    while ((c = getchar()) != '\n' && c != EOF);
}

individual* getIndividual(int id) {
    // Initialize a temporary individual structure and assign the head of the existing list to it
    individual* temp = sn1->indi;

    // Iterate through the existing list to find the individual with the specified ID
    while (temp != NULL && temp->mandInfo.id != id) {
        temp = temp->next;
    }

    // Return a pointer to the individual structure if found, or NULL if not found
    return temp;
}

group* getGroup(int id)
{
    group* temp=sn1->grp;
    while (temp != NULL && temp->mandInfo.id != id) {
        temp=temp->next;
    }
    return temp;
}

business* getBusiness(int id)
{
    business* temp=sn1->busi;
    while (temp != NULL && temp->mandInfo.id != id) {
        temp=temp->next;
    }
    return temp;
}

organization* getOrganization(int id)
{
    organization* temp=sn1->org;
    while (temp != NULL && temp->mandInfo.id != id) {
        temp=temp->next;
    }
    return temp;
}

network* initNetwork()
{
    network* sn=(network*)malloc(sizeof(network));
    sn->indi=NULL;
    sn->grp=NULL;
    sn->busi=NULL;
    sn->org=NULL;

    return sn;
}

mandatoryInfo initMandInfo()
{

    mandatoryInfo info;

    info.id=uniqueID();
    printf("Enter name:\n");
    scanf("\n%[^\n]s", info.name);
    time(&(info.creationTime));

    return info;
}

individual* initIndividual() {
    // Allocate memory for a new individual structure
    individual* indi = (individual*)malloc(sizeof(individual));

    // Initialize the mandatory information of the individual
    indi->mandInfo = initMandInfo();

    printf("Enter your birthday!\nEnter 1 to continue\t\tEnter -1 to skip\n\n");
    int in = 0;

    // Prompt the user to enter their birthday or skip the entry
    while (scanf("%d", &in) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }

    // If the user chooses to enter the birthday, call getDate function to get the date
    if (in == 1) {
        indi->bday = getDate();
    } else {
        indi->bday.day = -1;
    }

    // Initialize other fields of the individual structure
    indi->customerOf = NULL;
    indi->ownerOf = NULL;
    indi->inGroup = NULL;
    indi->inOrganization = NULL;
    indi->content = NULL;
    indi->next = NULL;

    // Allocate memory for a temporary individual structure and assign the head of the existing list to it
    individual* temp = (individual*)malloc(sizeof(individual));
    temp = sn1->indi;

    // If the existing list is empty, return the new individual as the head of the list
    if (temp == NULL) {
        return indi;
    }

    // Iterate through the existing list to find the end and append the new individual to the end of the list
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = indi;

    // Return the head of the updated list
    return sn1->indi;
}

void printAnIndividualPL(individualPL* temp)
{
    printf("%s\n", temp->indi->mandInfo.name);
}

void printIndividualPLs(individualPL* temp)
{
    while (temp != NULL) {
        if (temp->indi != NULL) {
            printAnIndividualPL(temp);
        }
        temp = temp->next;
    }
}

void printAGroupPL(groupPL* temp)
{
    printf("%s\n", temp->grp->mandInfo.name);
}

void printGroupPLs(groupPL* temp)
{
    while (temp != NULL) {
        printAGroupPL(temp);
        temp=temp->next;
    }
}

void printABusinessPL(businessPL* temp)
{
    printf("%s\n", temp->busi->mandInfo.name);
}

void printBusinessPLs(businessPL* temp)
{
    while (temp != NULL) {
        printABusinessPL(temp);
        temp=temp->next;
    }
}

void printAnOrganizationPL(organizationPL* temp)
{
    printf("%s\n", temp->org->mandInfo.name);
}

void printOrganizationPLs(organizationPL* temp)
{
    while (temp != NULL) {
        printAnOrganizationPL(temp);
        temp=temp->next;
    }
}

void printAnIndividual(individual* temp)
{
    printf("\n\nINDIVIDUAL ACCOUNT\nID = %d\n", temp->mandInfo.id);
    printf("Name = %s\n", temp->mandInfo.name);
    printf("Creation time = %s", ctime(&(temp->mandInfo.creationTime)));
    if (temp->bday.day != -1) {
        printf("birthday = ");
        printDate(temp->bday);
    }
    if (temp->inGroup != NULL) {
        groupPL* tempGrp=temp->inGroup;
        printf("\nMember of following groups:\n");
        printGroupPLs(tempGrp);
    } else {
        printf("\nIn no group\n");
    }
    if (temp->ownerOf != NULL) {
        businessPL* tempBusi=temp->ownerOf;
        printf("\nOwner of following businesses:\n");
        printBusinessPLs(tempBusi);
    } else {
        printf("\nOwning no business\n");
    }
    if (temp->customerOf != NULL) {
        businessPL* tempBusi=temp->customerOf;
        printf("\nCustomer of following businesses:\n");
        printBusinessPLs(tempBusi);
    } else {
        printf("\nCustomer of no business\n");
    }
    if (temp->inOrganization != NULL) {
        organizationPL* tempOrg=temp->inOrganization;
        printf("\nMember of following organizations:\n");
        printOrganizationPLs(tempOrg);
    } else {
        printf("\nIn no organization\n");
    }
}

void printIndividuals()
{
    individual* temp=sn1->indi;
    while (temp != NULL) {
        printAnIndividual(temp);
        temp=temp->next;
    }
}

individualPL* initIndividualPL(individualPL* ipl, int id)
{
    individualPL* indiPL=(individualPL*)malloc(sizeof(individualPL));
    indiPL->indi=getIndividual(id);
    if (indiPL->indi == NULL) {
        printf("Id not found!\n\n");
        return ipl;
    }
    indiPL->next=NULL;

    individualPL* temp=(individualPL*)malloc(sizeof(individualPL));

    temp=ipl;

    if (temp == NULL) {
        return indiPL;
    }
    while (temp->next != NULL) {
        if (temp->indi->mandInfo.id == id) {
            printf("Individual already added!\n\n");
            return ipl;
        }
        temp=temp->next;
    }
    if (temp->indi->mandInfo.id == id) {
        printf("Individual already added!\n\n");
    }
    temp->next=indiPL;

    return ipl;
}

businessPL* initBusinessPL(businessPL* bpl, int id)
{
    businessPL* busiPL=(businessPL*)malloc(sizeof(businessPL));
    busiPL->busi=getBusiness(id);
    if (busiPL->busi == NULL) {
        printf("Id not found!\n\n");
        return bpl;
    }
    busiPL->next=NULL;

    businessPL* temp=(businessPL*)malloc(sizeof(businessPL));

    temp=bpl;

    if (temp == NULL) {
        return busiPL;
    }
    while (temp->next != NULL) {
        if (temp->busi->mandInfo.id == id) {
            printf("Business already added!\n\n");
            return bpl;
        }
        temp=temp->next;
    }
    if (temp->busi->mandInfo.id == id) {
        printf("Business already added!\n\n");
        return bpl;
    }
    temp->next=busiPL;

    return bpl;
}

group* initBusinessPLForGroup(group* grp)
{
    printf("Enter business ID to add to the group %s\n\n", grp->mandInfo.name);
    int id;
    while (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }
    grp->busiMemPL=initBusinessPL(grp->busiMemPL, id);
    business* busi=getBusiness(id);
    if (busi == NULL) {
        return grp;
    }
    groupPL* gpl=(groupPL*)malloc(sizeof(groupPL));
    groupPL* temp=(groupPL*)malloc(sizeof(groupPL));

    gpl->grp=grp;
    gpl->next=NULL;


    temp=busi->inGroup;

    if (temp == NULL) {
        busi->inGroup=gpl;
        return grp;
    }
    while (temp->next != NULL) {
        if (temp->grp->mandInfo.id == grp->mandInfo.id) {
            return grp;
        }
        temp=temp->next;
    }
    if (temp->grp->mandInfo.id == grp->mandInfo.id) {
        return grp;
    }
    temp->next=gpl;

    return grp;
}

group* initIndividualPLForGroup(group* grp)
{
    printf("Enter individual ID to add to the group %s\n\n", grp->mandInfo.name);
    int id;
    while (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }
    grp->indiMemPL=initIndividualPL(grp->indiMemPL, id);
    individual* indi=getIndividual(id);
    if (indi == NULL) {
        return grp;
    }
    groupPL* gpl=(groupPL*)malloc(sizeof(groupPL));
    groupPL* temp=(groupPL*)malloc(sizeof(groupPL));

    gpl->grp=grp;
    gpl->next=NULL;

    temp=indi->inGroup;

    if (temp == NULL) {
        indi->inGroup=gpl;
        return grp;
    }
    while (temp->next != NULL) {
        if (temp->grp->mandInfo.id == grp->mandInfo.id) {
            return grp;
        }
        temp=temp->next;
    }
    if (temp->grp->mandInfo.id == grp->mandInfo.id) {
        return grp;
    }
    temp->next=gpl;

    return grp;
}

business* initIndividualPLForBusinessOwner(business* busi)
{
    printf("Enter individual ID to add owner to the business %s\n\n", busi->mandInfo.name);
    int id;
    while (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }
    busi->ownerPL=initIndividualPL(busi->ownerPL, id);
    individual* indi=getIndividual(id);
    if (indi == NULL) {
        return busi;
    }
    businessPL* bpl=(businessPL*)malloc(sizeof(businessPL));
    businessPL* temp=(businessPL*)malloc(sizeof(businessPL));

    bpl->busi=busi;
    bpl->next=NULL;


    temp=indi->ownerOf;

    if (temp == NULL) {
        indi->ownerOf=bpl;
        return busi;
    }
    while (temp->next != NULL) {
        if (temp->busi->mandInfo.id == busi->mandInfo.id) {
            return busi;
        }
        temp=temp->next;
    }
    if (temp->busi->mandInfo.id == busi->mandInfo.id) {
        return busi;
    }
    temp->next=bpl;

    return busi;
}

business* initIndividualPLForBusinessCustomer(business* busi)
{
    printf("Enter individual ID to add customer to the business %s\n\n", busi->mandInfo.name);
    int id;
    while (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }
    busi->customerPL=initIndividualPL(busi->customerPL, id);
    individual* indi=getIndividual(id);
    if (indi == NULL) {
        return busi;
    }
    businessPL* bpl=(businessPL*)malloc(sizeof(businessPL));
    businessPL* temp=(businessPL*)malloc(sizeof(businessPL));

    bpl->busi=busi;
    bpl->next=NULL;


    temp=indi->customerOf;

    if (temp == NULL) {
        indi->customerOf=bpl;
        return busi;
    }
    while (temp->next != NULL) {
        if (temp->busi->mandInfo.id == busi->mandInfo.id) {
            return busi;
        }
        temp=temp->next;
    }
    if (temp->busi->mandInfo.id == busi->mandInfo.id) {
        return busi;
    }
    temp->next=bpl;

    return busi;
}

organization* initIndividualPLForOrganization(organization* org) {
    printf("Enter individual ID to add to the organization %s\n\n", org->mandInfo.name);
    int id;
    while (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }

    // Add individual to organization's memberPL
    org->memberPL = initIndividualPL(org->memberPL, id);
    individual* indi = getIndividual(id);

    // If individual not found, return the organization without further modifications
    if (indi == NULL) {
        return org;
    }

    // Allocate memory for a new organizationPL node
    organizationPL* opl = (organizationPL*)malloc(sizeof(organizationPL));
    organizationPL* temp = (organizationPL*)malloc(sizeof(organizationPL));

    opl->org = org;
    opl->next = NULL;

    temp = indi->inOrganization;

    // If the individual is not already a member of the organization, add it
    if (temp == NULL) {
        indi->inOrganization = opl;
        return org;
    }

    while (temp->next != NULL) {
        if (temp->org->mandInfo.id == org->mandInfo.id) {
            return org;
        }
        temp = temp->next;
    }

    if (temp->org->mandInfo.id == org->mandInfo.id) {
        return org;
    }

    temp->next = opl;

    return org;
}

group* initGroup()
{
    group* grp=(group*)malloc(sizeof(group));
    grp->mandInfo=initMandInfo();

    grp->indiMemPL=NULL;
    grp->busiMemPL=NULL;
    grp->content=NULL;
    grp->next=NULL;

    int in=0;
    do {
        printf("Enter 1 to add an individual to this group\nEnter 2 to add a business to this group\nEnter -1 to finish group creation\n");

        while (scanf("%d", &in) != 1) {
            printf("Invalid input. Please enter a valid integer.\n\n");
            clearInputBuffer();
        }

        switch (in) {
        case 1:
            grp=initIndividualPLForGroup(grp);
            break;

        case 2:
            grp=initBusinessPLForGroup(grp);
            break;

        default:
            break;
        }

    } while (in != -1);

    group* temp=(group*)malloc(sizeof(group));

    temp=sn1->grp;

    if (sn1->grp == NULL) {
        return grp;
    }
    while (temp->next != NULL) {
        temp=temp->next;
    }
    temp->next=grp;

    return sn1->grp;
}

void printAGroup(group* temp)
{
    printf("\n\nGROUP ACCOUNT\nID = %d\n", temp->mandInfo.id);
    printf("Name = %s\n", temp->mandInfo.name);
    printf("Creation time = %s\n", ctime(&(temp->mandInfo.creationTime)));
    if (temp->indiMemPL != NULL) {
        printf("\nIndividual members of the group %s:\n", temp->mandInfo.name);
        printIndividualPLs(temp->indiMemPL);
    }
    if (temp->busiMemPL != NULL) {
        printf("\nBusiness members of the group %s:\n", temp->mandInfo.name);
        printBusinessPLs(temp->busiMemPL);
    }
}

void printGroups()
{
    group* temp=sn1->grp;
    while (temp != NULL) {
        printAGroup(temp);
        temp=temp->next;
    }
}

business* initBusiness()
{
    business* busi=(business*)malloc(sizeof(business));
    busi->mandInfo=initMandInfo();
    printf("\nEnter your LOCATION\n");
    busi->loc=getCoord2D();
    busi->ownerPL=NULL;
    busi->customerPL=NULL;
    busi->inGroup=NULL;
    busi->content=NULL;
    busi->next=NULL;

    int in=0, in2=0;
    do {
        printf("Enter 1 to add an owner to this business\nEnter 2 to add a customer to this business\nEnter -1 to finish business creation\n");

        while (scanf("%d", &in) != 1) {
            printf("Invalid input. Please enter a valid integer.\n\n");
            clearInputBuffer();
        }

        switch (in) {
        case -1:
            break;

        case 1:
            busi=initIndividualPLForBusinessOwner(busi);
            break;

        case 2:
            busi=initIndividualPLForBusinessCustomer(busi);
            break;

        default:
            printf("Invalid input!\n\n");
            break;
        }

    } while (in != -1);

    business* temp=(business*)malloc(sizeof(business));

    temp=sn1->busi;

    if (sn1->busi == NULL) {
        return busi;
    }
    while (temp->next != NULL) {
        temp=temp->next;
    }
    temp->next=busi;

    return sn1->busi;
}

void printABusiness(business* temp)
{
    printf("\n\nBUSINESS ACCOUNT\nID = %d\n", temp->mandInfo.id);
    printf("Name = %s\n", temp->mandInfo.name);
    printf("Creation time = %s\n", ctime(&(temp->mandInfo.creationTime)));
    printf("Location:\nX coordinate: %.2f\tY coordinate: %.2f\n", temp->loc.x, temp->loc.y);

    if (temp->ownerPL != NULL) {
        printf("\nOwners of the business %s:\n", temp->mandInfo.name);
        printIndividualPLs(temp->ownerPL);
    }
    if (temp->customerPL != NULL) {
        printf("\nCustomers of the business %s:\n", temp->mandInfo.name);
        printIndividualPLs(temp->customerPL);
    }
    if (temp->inGroup != NULL) {
        groupPL* tempGrp=temp->inGroup;
        printf("\nMember of following groups:\n");
        printGroupPLs(tempGrp);
    } else {
        printf("\nIn no group currently!\n");
    }
}

void printBusinesses()
{
    business* temp=sn1->busi;
    while (temp != NULL) {
        printABusiness(temp);
        temp=temp->next;
    }
}

organization* initOrganization()
{
    organization* org=(organization*)malloc(sizeof(organization));
    org->mandInfo=initMandInfo();
    printf("\nEnter your LOCATION\n");
    org->loc=getCoord2D();
    org->memberPL=NULL;
    org->content=NULL;
    org->next=NULL;

    int in=0;
    do {
        printf("Enter 1 to add a member to this organization\nEnter -1 to finish organization creation\n");

        while (scanf("%d", &in) != 1) {
            printf("Invalid input. Please enter a valid integer.\n\n");
            clearInputBuffer();
        }

        switch (in) {
        case 1:
            org=initIndividualPLForOrganization(org);
            break;

        default:
            break;
        }

    } while (in != -1);

    organization* temp=(organization*)malloc(sizeof(organization));

    temp=sn1->org;

    if (sn1->org == NULL) {
        return org;
    }
    while (temp->next != NULL) {
        temp=temp->next;
    }
    temp->next=org;

    return sn1->org;
}

void printAnOrganization(organization* temp)
{
    printf("\n\nORGANIZATION ACCOUNT\nID = %d\n", temp->mandInfo.id);
    printf("Name = %s\n", temp->mandInfo.name);
    printf("Creation time = %s\n", ctime(&(temp->mandInfo.creationTime)));
    printf("Location:\nX coordinate: %.2f\tY coordinate: %.2f\n", temp->loc.x, temp->loc.y);

    if (temp->memberPL != NULL) {
        printf("\nMembers of the organization %s:\n", temp->mandInfo.name);
        printIndividualPLs(temp->memberPL);
    }
}

void printOrganizations()
{
    organization* temp=sn1->org;
    while (temp != NULL) {
        printAnOrganization(temp);
        temp=temp->next;
    }
}

void searchByType()
{
    printf("Enter 1 to search individuals\nEnter 2 to search groups\nEnter 3 to search businesses\nEnter 4 to search organizations\n");
    int type;
    while (scanf("%d", &type) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }
    switch (type) {
    case 1:
        printIndividuals();
        break;

    case 2:
        printGroups();
        break;

    case 3:
        printBusinesses();
        break;

    case 4:
        printOrganizations();
        break;

    default:
        break;
    }
}

int searchIndividualByName(char* s)
{
    individual* temp=sn1->indi;
    int flag=0;
    while (temp!=NULL) {
        strcmp(temp->mandInfo.name, s) == 0 ? printAnIndividual(temp), flag=1 : 1 ;
        temp=temp->next;
    }
    return (flag == 0 ? 0 : 1);
}

void searchIndividualByBDay()
{
    individual* temp=sn1->indi;
    date d1;
    d1=getDate();
    int flag=0;
    while (temp!=NULL) {
        datecmp(temp->bday, d1) == 0 ? printAnIndividual(temp), flag=1 : 1 ;
        temp=temp->next;
    }
    (flag == 0 ? printf("Not found!\n") : 1);
}

int searchGroupByName(char* s)
{
    group* temp=sn1->grp;
    int flag=0;
    while (temp!=NULL) {
        strcmp(temp->mandInfo.name, s) == 0 ? printAGroup(temp), flag=1  : 1 ;
        temp=temp->next;
    }
    return (flag == 0 ? 0 : 1);
}

int searchBusinessByName(char* s)
{
    business* temp=sn1->busi;
    int flag=0;
    while (temp!=NULL) {
        strcmp(temp->mandInfo.name, s) == 0 ? printABusiness(temp), flag=1  : 1 ;
        temp=temp->next;
    }
    return (flag == 0 ? 0 : 1);
}

int searchOrganizationByName(char* s)
{
    organization* temp=sn1->org;
    int flag=0;
    while (temp!=NULL) {
        strcmp(temp->mandInfo.name, s) == 0 ? printAnOrganization(temp), flag=1  : 1 ;
        temp=temp->next;
    }
    return (flag == 0 ? 0 : 1);
}

void searchByName()
{
    printf("\nEnter the name you want to search\n");
    char s[50];
    scanf("\n%[^\n]s", s);
    int flag=0;
    if (searchIndividualByName(s)) {
        flag=1;
    }
    if (searchGroupByName(s)) {
        flag=1;
    }
    if (searchBusinessByName(s)) {
        flag=1;
    }
    if (searchOrganizationByName(s)) {
        flag=1;
    }
    // Print "Not found!" message if no match is found
    flag == 0 ? printf("Not found!\n\n"): 1 ;

}

void printIndividualsInAGroup( group* grp)
{
    printf("\nIndividuals in the group %s:\n", grp->mandInfo.name);
    printIndividualPLs(grp->indiMemPL);
}

void printIndividualsInGroups(groupPL* temp)
{
    while (temp != NULL) {
        printIndividualsInAGroup(temp->grp);
        temp=temp->next;
    }
}

void printBusinessesInAGroup( group* grp)
{
    printf("\nBusinesses in the group %s:\n", grp->mandInfo.name);
    printBusinessPLs(grp->busiMemPL);
}

void printBusinessesInGroups(groupPL* temp)
{
    while (temp != NULL) {
        printBusinessesInAGroup(temp->grp);
        temp=temp->next;
    }
}

void printIndividualsInABusiness(business* busi)
{
    printf("\nOwners of the business %s:\n", busi->mandInfo.name);
    printIndividualPLs(busi->ownerPL);
    printf("\nCustomers of the business %s:\n", busi->mandInfo.name);
    printIndividualPLs(busi->customerPL);
}

void printIndividualsInBusinesses(businessPL* temp)
{
    while (temp != NULL) {
        printIndividualsInABusiness(temp->busi);
        temp=temp->next;
    }
}

void printIndividualsInAnOrganization( organization* org)
{
    printf("\nIndividuals in the organization %s:\n", org->mandInfo.name);
    printIndividualPLs(org->memberPL);
}

void printIndividualsInOrganizations(organizationPL* temp)
{
    while (temp != NULL) {
        printIndividualsInAnOrganization(temp->org);
        temp=temp->next;
    }
}


void printLinksInAnIndividual(individual* indi)
{
    printf("\nIndividual %s in the following groups\n", indi->mandInfo.name);
    printGroupPLs(indi->inGroup);
    printf("\nIndividual %s is the owner of following businesses\n", indi->mandInfo.name);
    printBusinessPLs(indi->ownerOf);
    printf("\nIndividual %s is the customer of following businesses\n", indi->mandInfo.name);
    printBusinessPLs(indi->customerOf);
    printf("\nIndividual %s in the following organizations\n", indi->mandInfo.name);
    printOrganizationPLs(indi->inOrganization);
}

void printLinksInIndividuals(individualPL* temp)
{
    while (temp != NULL) {
        printLinksInAnIndividual(temp->indi);
        temp=temp->next;
    }
}

void printIndividuals1Hop(individual* indi)
{
    printf("\nIndividuals in the groups of which you are a member\n");
    printIndividualsInGroups(indi->inGroup);
    printf("\nBusinesses in the groups of which you are a member\n");
    printBusinessesInGroups(indi->inGroup);
    printf("\nIndividuals in the businesses of which you are an owner\n");
    printIndividualsInBusinesses(indi->ownerOf);
    printf("\nIndividuals in the businesses of which you are a customer\n");
    printIndividualsInBusinesses(indi->customerOf);
    printf("\nIndividuals in the organizations of which you are a member\n");
    printIndividualsInOrganizations(indi->inOrganization);
}

void printGroups1Hop(group* grp)
{
    printf("\nLinks of the member Individuals\n");
    printLinksInIndividuals(grp->indiMemPL);
    printf("\nMembers of the member businesses\n");
    printIndividualsInBusinesses(grp->busiMemPL);
}

void printBusinesses1Hop(business* busi)
{
    printf("\nLinks of the owners\n");
    printLinksInIndividuals(busi->ownerPL);
    printf("\nLinks of the customers\n");
    printLinksInIndividuals(busi->customerPL);
}

void printOrganizations1Hop(organization* org)
{
    printf("\nLinks of the member individuals\n");
    printLinksInIndividuals(org->memberPL);
}

void deleteIndividualFromIndividualPL(int id, individualPL** iplPtr)
{
    individualPL* temp=*iplPtr;
    individualPL* prev = NULL;

    // If the head node itself holds the key to be deleted
    if (temp != NULL && temp->indi->mandInfo.id == id) {
        *iplPtr = temp->next; // Change the head
        free(temp);         // Free the old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->indi->mandInfo.id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the key was not present in the linked list
    if (temp == NULL) {
        printf("Key not found in the linked list.\n\n");
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;

    // Free the memory of the node to be deleted
    free(temp);
}

void deleteIndividualFromGroups(individual* indi)
{
    groupPL* temp=indi->inGroup;

    while(temp != NULL) {
        deleteIndividualFromIndividualPL(indi->mandInfo.id, &(temp->grp->indiMemPL));
        temp=temp->next;
    }
}

void deleteIndividualFromBusinessesAsOwner(individual* indi)
{
    businessPL* temp=indi->ownerOf;

    while(temp != NULL) {
        deleteIndividualFromIndividualPL(indi->mandInfo.id, &(temp->busi->ownerPL));
        temp=temp->next;
    }
}

void deleteIndividualFromBusinessesAsCustomer(individual* indi)
{
    businessPL* temp=indi->customerOf;

    while(temp != NULL) {
        deleteIndividualFromIndividualPL(indi->mandInfo.id, &(temp->busi->customerPL));
        temp=temp->next;
    }
}

void deleteIndividualFromOrganizations(individual* indi)
{
    organizationPL* temp=indi->inOrganization;

    while(temp != NULL) {
        deleteIndividualFromIndividualPL(indi->mandInfo.id, &(temp->org->memberPL));
        temp=temp->next;
    }
}

void deleteIndividualSelf(int id)
{
    individual* temp=sn1->indi;
    individual* prev = NULL;

    // If the head node itself holds the key to be deleted
    if (temp != NULL && temp->mandInfo.id == id) {
        sn1->indi = temp->next; // Change the head
        free(temp);         // Free the old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->mandInfo.id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the key was not present in the linked list
    if (temp == NULL) {
        printf("Key not found in the linked list.\n\n");
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;

    // Free the memory of the node to be deleted
    free(temp);
}

void deleteIndividual(individual* indi)
{
    deleteIndividualFromGroups(indi);
    deleteIndividualFromBusinessesAsOwner(indi);
    deleteIndividualFromBusinessesAsCustomer(indi);
    deleteIndividualFromOrganizations(indi);
    deleteIndividualSelf(indi->mandInfo.id);
}

void deleteGroupFromGroupPL(int id, groupPL** gplPtr)
{
    groupPL* temp=*gplPtr;
    groupPL* prev = NULL;

    // If the head node itself holds the key to be deleted
    if (temp != NULL && temp->grp->mandInfo.id == id) {
        *gplPtr = temp->next; // Change the head
        free(temp);         // Free the old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->grp->mandInfo.id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the key was not present in the linked list
    if (temp == NULL) {
        printf("Key not found in the linked list.\n\n");
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;

    // Free the memory of the node to be deleted
    free(temp);
}

void deleteGroupFromIndividuals(group* grp) {
    individualPL* temp = grp->indiMemPL;

    while (temp != NULL) {
        deleteGroupFromGroupPL(grp->mandInfo.id, &(temp->indi->inGroup));
        temp = temp->next;
    }
}

void deleteGroupFromBusinesses(group* grp) {
    // Iterate through the linked list of businesses associated with the group
    businessPL* temp = grp->busiMemPL;
    while(temp != NULL) {
        // Remove the reference to the group from the linked business
        deleteGroupFromGroupPL(grp->mandInfo.id, &(temp->busi->inGroup));
        temp = temp->next;
    }
}

void deleteGroupSelf(int id)
{
    group* temp=sn1->grp;
    group* prev = NULL;

    // If the head node itself holds the key to be deleted
    if (temp != NULL && temp->mandInfo.id == id) {
        sn1->grp = temp->next; // Change the head
        free(temp);         // Free the old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->mandInfo.id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the key was not present in the linked list
    if (temp == NULL) {
        printf("Key not found in the linked list.\n\n");
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;

    // Free the memory of the node to be deleted
    free(temp);
}

void deleteGroup(group* grp) {
    // Remove references to the group from individuals
    deleteGroupFromIndividuals(grp);
    
    // Remove references to the group from businesses
    deleteGroupFromBusinesses(grp);
    
    // Delete the group node itself
    deleteGroupSelf(grp->mandInfo.id);
}

void deleteBusinessFromBusinessPL(int id, businessPL** bplPtr)
{
    businessPL* temp=*bplPtr;
    businessPL* prev = NULL;

    // If the head node itself holds the key to be deleted
    if (temp != NULL && temp->busi->mandInfo.id == id) {
        *bplPtr = temp->next; // Change the head
        free(temp);         // Free the old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->busi->mandInfo.id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the key was not present in the linked list
    if (temp == NULL) {
        printf("Key not found in the linked list.\n\n");
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;

    // Free the memory of the node to be deleted
    free(temp);
}

void deleteBusinessFromIndividualsOwners(business* busi) {
    // Iterate through the linked list of individuals who are owners of the business
    individualPL* temp = busi->ownerPL;

    while (temp != NULL) {
        // Remove references to the business from the ownerOf field of the current individual
        deleteBusinessFromBusinessPL(busi->mandInfo.id, &(temp->indi->ownerOf));
        temp = temp->next;
    }
}

void deleteBusinessFromIndividualsCustomers(business* busi) {
    // Iterate through the linked list of individuals who are customers of the business
    individualPL* temp = busi->customerPL;

    while (temp != NULL) {
        // Remove references to the business from the customerOf field of the current individual
        deleteBusinessFromBusinessPL(busi->mandInfo.id, &(temp->indi->customerOf));
        temp = temp->next;
    }
}

void deleteBusinessFromGroups(business* busi) {
    // Iterate through the linked list of groups associated with the business
    groupPL* temp = busi->inGroup;

    while (temp != NULL) {
        // Remove references to the business from the business member list of the current group
        deleteBusinessFromBusinessPL(busi->mandInfo.id, &(temp->grp->busiMemPL));
        temp = temp->next;
    }
}

void deleteBusinessSelf(int id)
{
    business* temp=sn1->busi;
    business* prev = NULL;

    // If the head node itself holds the key to be deleted
    if (temp != NULL && temp->mandInfo.id == id) {
        sn1->busi = temp->next; // Change the head
        free(temp);         // Free the old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->mandInfo.id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the key was not present in the linked list
    if (temp == NULL) {
        printf("Key not found in the linked list.\n\n");
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;

    // Free the memory of the node to be deleted
    free(temp);
}

void deleteBusiness(business* busi) {
    // Remove references to the business from linked groups
    deleteBusinessFromGroups(busi);

    // Remove references to the business from linked business owners
    deleteBusinessFromIndividualsOwners(busi);

    // Remove references to the business from linked business customers
    deleteBusinessFromIndividualsCustomers(busi);

    // Perform the self-deletion of the business
    deleteBusinessSelf(busi->mandInfo.id);
}

void deleteOrganizationFromOrganizationPL(int id, organizationPL** oplPtr)
{
    organizationPL* temp=*oplPtr;
    organizationPL* prev = NULL;

    // If the head node itself holds the key to be deleted
    if (temp != NULL && temp->org->mandInfo.id == id) {
        *oplPtr = temp->next; // Change the head
        free(temp);         // Free the old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->org->mandInfo.id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the key was not present in the linked list
    if (temp == NULL) {
        printf("Key not found in the linked list.\n\n");
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;

    // Free the memory of the node to be deleted
    free(temp);
}

void deleteOrganizationFromIndividuals(organization* org) {
    // Initialize a pointer to the linked list of individuals
    individualPL* temp = org->memberPL;

    // Iterate through the linked list of individuals
    while (temp != NULL) {
        // Remove the organization reference from the individual's organization pointer
        deleteOrganizationFromOrganizationPL(org->mandInfo.id, &(temp->indi->inOrganization));

        // Move to the next individual in the list
        temp = temp->next;
    }
}

void deleteOrganizationSelf(int id)
{
    organization* temp=sn1->org;
    organization* prev = NULL;

    // If the head node itself holds the key to be deleted
    if (temp != NULL && temp->mandInfo.id == id) {
        sn1->org = temp->next; // Change the head
        free(temp);         // Free the old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->mandInfo.id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the key was not present in the linked list
    if (temp == NULL) {
        printf("Key not found in the linked list.\n\n");
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;

    // Free the memory of the node to be deleted
    free(temp);
}

void deleteOrganization(organization* org) {
    // Remove references to the organization from linked individuals
    deleteOrganizationFromIndividuals(org);

    // Delete the organization itself
    deleteOrganizationSelf(org->mandInfo.id);
}

stringPL* initStringPL(stringPL* spl) {
    // Allocate memory for a new stringPL node
    stringPL* strPL = (stringPL*)malloc(sizeof(stringPL));

    // Read a string from the user and assign it to the string field of the new node
    scanf("\n%[^\n]s", strPL->string);

    // Initialize the next pointer of the new node to NULL
    strPL->next = NULL;

    // Allocate memory for a temporary stringPL node and assign the head of the existing list to it
    stringPL* temp = (stringPL*)malloc(sizeof(stringPL));
    temp = spl;

    // If the existing list is empty, return the new node as the head of the list
    if (temp == NULL) {
        return strPL;
    }

    // Iterate through the existing list to check if the entered content already exists
    while (temp->next != NULL) {
        if (strcmp(temp->string, strPL->string) == 0) {
            // If duplicate content is found, print a message and return the original head of the list
            printf("Content already posted!\n\n");
            return spl;
        }
        temp = temp->next;
    }

    // Check the last node in the list for duplicate content
    if (strcmp(temp->string, strPL->string) == 0) {
        // If duplicate content is found, print a message and return the original head of the list
        printf("Content already posted!\n\n");
        return spl;
    }

    // Append the new node to the end of the list
    temp->next = strPL;

    // Return the head of the updated list
    return spl;
}

void printContentsByAnIndividual(individual* indi) {
    // Initialize a temporary pointer to the stringPL structure using the individual pointer
    if (indi == NULL || indi->content == NULL) {
        return;
    }
    stringPL* temp = indi->content;

    // Iterate through the content of the individual
    while (temp != NULL) {
        // Print each content item along with the name of the individual
        printf("\nContent \"%s\" posted by individual %s\n", temp->string, indi->mandInfo.name);
        temp = temp->next;
    }
}

void printContentByIndividualsMembersOfOrganizationPL(organizationPL* opl) {
    // Initialize a temporary pointer to the individualPL structure using the organizationPL pointer
    if (opl == NULL || opl->org == NULL || opl->org->memberPL == NULL) {
        return;
    }
    individualPL* temp = opl->org->memberPL;

    // Iterate through the individual members of the organization
    while (temp != NULL) {
        // Call printContentsByAnIndividual for each individual to print their content
        printContentsByAnIndividual(temp->indi);
        temp = temp->next;
    }
}

void printContentByIndividualsMembersOfGroupPL(groupPL* gpl) {
    if (gpl == NULL || gpl->grp == NULL) {
        return;
    }
    individualPL* temp=gpl->grp->indiMemPL;

    while (temp != NULL) {
        printContentsByAnIndividual(temp->indi);
        temp=temp->next;
    }
}

void printContentByIndividuals2LinkedToIndividual(individual* indi) {
    if (indi == NULL) {
        return;
    }
    // Check if the individual is a member of any group
    if (indi->inGroup != NULL) {
        // Print content by individuals in the group
        printContentByIndividualsMembersOfGroupPL(indi->inGroup);
    }

    // Check if the individual is a member of any organization
    if (indi->inOrganization != NULL) {
        // Print content by individuals in the organization
        printContentByIndividualsMembersOfOrganizationPL(indi->inOrganization);
    }
}

void goToIndividual() {
    int id;
    printf("\n\nEnter id of your account to login\n");

    // Validate and retrieve user input for individual ID
    while (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }

    // Attempt to retrieve individual information
    individual* indi = getIndividual(id);

    // Check if individual is found
    if (indi == NULL) {
        printf("Not found!\n\n");
        return;
    }

    // Display welcome message
    printf("\nWelcome %s!\n\n", indi->mandInfo.name);

    int in=0, in2=0;
    int exitFlag = 0;  // Flag to track the exit condition

    do {
        if (indi->bday.day == -1) {
            printf("Enter 1 to add birthday!\n");
        } else {
            printf("Enter 1 to change birthday!\n");
        }
        printf("Enter 2 to post content\n"
               "Enter 3 to print all 1 hop linked nodes\n"
               "Enter 4 to print content posted by individuals linked to %s\n"
               "Enter 5 to delete this account\n"
               "Enter -1 to exit\n\n", indi->mandInfo.name);

        // Validate and retrieve user input for menu selection
        while (scanf("%d", &in) != 1) {
            printf("Invalid input. Please enter a valid integer.\n\n");
            clearInputBuffer();
        }

        // Switch based on user's choice
        switch (in) {
            case -1:
                // Ask for exit confirmation
                printf("Do you want to exit %s\nEnter 1 to exit\t\tEnter 0 to cancel\n", indi->mandInfo.name);
                while (scanf("%d", &in2) != 1) {
                    printf("Invalid input. Please enter a valid integer.\n\n");
                    clearInputBuffer();
                }
                if (in2 == 1) {
                    exitFlag = 1;  // Set the exitFlag to 1 to exit the loop
                    return;
                } else {
                    break;
                }
            case 1:
                // Add or change birthday
                indi->bday = getDate();
                printf("Your birthday:\n");
                printDate(indi->bday);
                break;
            case 2:
                printf("Type your content to post:\n");
                indi->content = initStringPL(indi->content);
                break;
            case 3:
                printIndividuals1Hop(indi);
                break;
            case 4:
                printContentByIndividuals2LinkedToIndividual(indi);
                break;
            case 5:
                // Ask for delete confirmation
                printf("Do you want to delete account %s?\nEnter 1 to delete\nEnter 0 to cancel\n", indi->mandInfo.name);
                while (scanf("%d", &in2) != 1) {
                    printf("Invalid input. Please enter a valid integer.\n\n");
                    clearInputBuffer();
                }
                if (in2 == 1) {
                    deleteIndividual(indi);
                    printf("Account deleted.\n");
                    return;
                } else {
                    printf("Account not deleted.\n");
                }
                break;
            default:
                printf("Invalid input!\n\n");
                break;
        }
    } while (!exitFlag);
}

void goToGroup() {
    int id;
    printf("\nEnter id of your account to login\n");

    // Validate and retrieve user input for group ID
    while (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }

    // Attempt to retrieve group information
    group* grp = getGroup(id);

    // Check if group is found
    if (grp == NULL) {
        printf("Not found!\n\n");
        return;
    }

    // Display welcome message
    printf("\nWelcome %s!\n", grp->mandInfo.name);

    int in, in2;
    int exitFlag = 0;  // Flag to track the exit condition
    do {
        // Display group menu options
        printf("Enter 1 to post content\n"
               "Enter 2 to print all 1 hop linked nodes\n"
               "Enter 3 to add an individual to the group %s\n"
               "Enter 4 to add a business to the group %s\n"
               "Enter 5 to delete this account\n"
               "Enter -1 to exit\n\n", grp->mandInfo.name, grp->mandInfo.name);

        // Validate and retrieve user input for menu selection
        while (scanf("%d", &in) != 1) {
            printf("Invalid input. Please enter a valid integer.\n\n");
            clearInputBuffer();
        }

        // Switch based on user's choice
        switch (in) {
            case -1:
                // Ask for exit confirmation
                printf("Do you want to exit %s\nEnter 1 to exit\t\tEnter 0 to cancel\n", grp->mandInfo.name);
                while (scanf("%d", &in2) != 1) {
                    printf("Invalid input. Please enter a valid integer.\n\n");
                    clearInputBuffer();
                }
                if (in2 == 1) {
                    exitFlag = 1;  // Set the exitFlag to 1 to exit the loop
                    return;
                } else {
                    break;
                }
            case 1:
                printf("Type your content to post:\n");
                grp->content = initStringPL(grp->content);
                break;
            case 2:
                printGroups1Hop(grp);
                break;
            case 3:
                grp = initIndividualPLForGroup(grp);
                break;
            case 4:
                grp = initBusinessPLForGroup(grp);
                break;
            case 5:
                // Ask for delete confirmation
                printf("Do you want to delete account %s?\nEnter 1 to delete\nEnter 0 to cancel\n", grp->mandInfo.name);
                while (scanf("%d", &in2) != 1) {
                    printf("Invalid input. Please enter a valid integer.\n\n");
                    clearInputBuffer();
                }
                if (in2 == 1) {
                    deleteGroup(grp);
                    printf("Account deleted.\n");
                    return;
                } else {
                    printf("Account not deleted.\n");
                }
                break;
            default:
                break;
        }
    } while (!exitFlag);
}

void goToBusiness() {
    int id;
    printf("\nEnter id of your account to login\n");

    // Validate and retrieve user input for business ID
    while (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }

    // Attempt to retrieve business information
    business* busi = getBusiness(id);

    // Check if business is found
    if (busi == NULL) {
        printf("Not found!\n\n");
        return;
    }

    // Display welcome message
    printf("\nWelcome %s!\n", busi->mandInfo.name);

    int in, in2;
    int exitFlag = 0;  // Flag to track the exit condition

    do {
        // Display business menu options
        printf("Enter 1 to change location information\n"
               "Enter 2 to post content\n"
               "Enter 3 to print all 1 hop linked nodes\n"
               "Enter 4 to add an owner to the business %s\n"
               "Enter 5 to add a customer to the business %s\n"
               "Enter 6 to delete this account\n"
               "Enter -1 to exit\n\n", busi->mandInfo.name, busi->mandInfo.name);

        // Validate and retrieve user input for menu selection
        while (scanf("%d", &in) != 1) {
            printf("Invalid input. Please enter a valid integer.\n\n");
            clearInputBuffer();
        }

        // Switch based on user's choice
        switch (in) {
            case -1:
                // Ask for exit confirmation
                printf("Do you want to exit %s\nEnter 1 to exit\t\tEnter 0 to cancel\n", busi->mandInfo.name);
                while (scanf("%d", &in2) != 1) {
                    printf("Invalid input. Please enter a valid integer.\n\n");
                    clearInputBuffer();
                }
                if (in2 == 1) {
                    exitFlag = 1;  // Set the exitFlag to 1 to exit the loop
                    return;
                } else {
                    break;
                }
            case 1:
                printf("\nEnter your NEW LOCATION\n");
                busi->loc = getCoord2D();
                break;
            case 2:
                printf("Type your content to post:\n");
                busi->content = initStringPL(busi->content);
                break;
            case 3:
                printBusinesses1Hop(busi);
                break;
            case 4:
                busi = initIndividualPLForBusinessOwner(busi);
                break;
            case 5:
                busi = initIndividualPLForBusinessCustomer(busi);
                break;
            case 6:
                // Ask for delete confirmation
                printf("Do you want to delete account %s?\nEnter 1 to delete\nEnter 0 to cancel\n", busi->mandInfo.name);
                while (scanf("%d", &in2) != 1) {
                    printf("Invalid input. Please enter a valid integer.\n\n");
                    clearInputBuffer();
                }
                if (in2 == 1) {
                    deleteBusiness(busi);
                    printf("Account deleted.\n");
                    return;
                } else {
                    printf("Account not deleted.\n");
                }
                break;
            default:
                printf("Invalid input!\n\n");
                break;
        }
    } while (!exitFlag);
}

void goToOrganization() {
    int id;
    printf("\nEnter id of your account to login\n");

    // Validate and retrieve user input for organization ID
    while (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a valid integer.\n\n");
        clearInputBuffer();
    }

    // Attempt to retrieve organization information
    organization* org = getOrganization(id);

    // Check if organization is found
    if (org == NULL) {
        printf("Not found!\n\n");
        return;
    }

    // Display welcome message
    printf("\nWelcome %s!\n", org->mandInfo.name);

    int in;
    do {
        // Display organization menu options
        printf("Enter 1 to change your location information\n"
               "Enter 2 to post content\n"
               "Enter 3 to print all 1 hop linked nodes\n"
               "Enter 4 to add an individual to the organization %s\n"
               "Enter 5 to delete this account\n"
               "Enter -1 to exit\n\n", org->mandInfo.name);

        // Validate and retrieve user input for menu selection
        while (scanf("%d", &in) != 1) {
            printf("Invalid input. Please enter a valid integer.\n\n");
            clearInputBuffer();
        }

        // Switch based on user's choice
        switch (in) {
            case -1:
                return;
            case 1:
                printf("\nEnter your NEW LOCATION\n");
                org->loc = getCoord2D();
                break;
            case 2:
                printf("Type your content to post:\n");
                org->content = initStringPL(org->content);
                break;
            case 3:
                printOrganizations1Hop(org);
                break;
            case 4:
                org = initIndividualPLForOrganization(org);
                break;
            case 5:
                // Ask user if they want to delete the account
                printf("Do you want to delete the account %s?\nEnter 1 to delete\nEnter 0 to cancel\n", org->mandInfo.name);
                while (scanf("%d", &in) != 1) {
                    printf("Invalid input. Please enter a valid integer.\n\n");
                    clearInputBuffer();
                }
                if (in == 1) {
                    deleteOrganization(org);
                    return;
                }
                break;
            default:
                printf("Invalid input!\n\n");
                break;
        }
    } while (in != -1);
}

void searchForContentByAnIndividual(individual* indi, char* s) {
    // Initialize a temporary pointer to traverse the linked list of strings (content) within the individual
    stringPL* temp = indi->content;

    // Iterate through the linked list of content within the individual
    while (temp != NULL) {
        // Check if the content matches the specified keyword
        if (strcmp(temp->string, s) == 0) {
            // Print a message indicating the content is posted by the current individual
            printf("\nContent \"%s\" posted by individual %s\n", s, indi->mandInfo.name);
        }

        // Move to the next content node within the individual
        temp = temp->next;
    }
}

void searchForContentByIndividuals(individual* indi, char* s)
{
    // Initialize a temporary pointer to traverse the linked list of individuals
    individual* temp = indi;

    // Iterate through the linked list of individuals
    while (temp != NULL) {
        // Search for content in the current individual
        searchForContentByAnIndividual(temp, s);

        // Move to the next individual in the linked list
        temp = temp->next;
    }
}

void searchForContentByAGroup(group* grp, char* s)
{
    // Initialize a temporary pointer to traverse the linked list of strings (content) within the group
    stringPL* temp = grp->content;

    // Iterate through the linked list of content within the group
    while (temp != NULL) {
        // Check if the content matches the specified keyword
        if (strcmp(temp->string, s) == 0) {
            // Print a message indicating the content is posted by the current group
            printf("\nContent \"%s\" posted by group %s\n", s, grp->mandInfo.name);
        }

        // Move to the next content node within the group
        temp = temp->next;
    }
}

void searchForContentByGroups(group* grp, char* s)
{
    // Initialize a temporary pointer to traverse the linked list of groups
    group* temp = grp;

    // Iterate through the linked list of groups
    while (temp != NULL) {
        // Call the function to search for content within the current group
        searchForContentByAGroup(temp, s);

        // Move to the next group in the linked list
        temp = temp->next;
    }
}

void searchForContentByABusiness(business* busi, char* s)
{
    // Initialize a temporary pointer to traverse the linked list of content in the business
    stringPL* temp = busi->content;

    // Iterate through the linked list of content in the business
    while (temp != NULL) {
        // Check if the content matches the specified string
        if (strcmp(temp->string, s) == 0) {
            // Print a message indicating the content was posted by the business
            printf("\nContent \"%s\" posted by business %s\n", s, busi->mandInfo.name);
        }

        // Move to the next content node in the linked list
        temp = temp->next;
    }
}

void searchForContentByBusinesses(business* busi, char* s)
{
    // Initialize a temporary pointer to traverse the linked list of businesses
    business* temp = busi;

    // Iterate through the linked list of businesses
    while (temp != NULL) {
        // Call a function to search for content within the current business
        searchForContentByABusiness(temp, s);

        // Move to the next business in the linked list
        temp = temp->next;
    }
}

void searchForContentByAnOrganization(organization* org, char* s)
{
    // Initialize a temporary pointer to traverse the linked list of content
    stringPL* temp = org->content;

    // Iterate through the linked list of content
    while (temp != NULL) {
        // Compare the current content string with the search term
        if (strcmp(temp->string, s) == 0) {
            // Print a message indicating the presence of the content
            printf("\nContent \"%s\" posted by organization %s\n", s, org->mandInfo.name);
        }

        // Move to the next content string in the linked list
        temp = temp->next;
    }
}

void searchForContentByOrganizations(organization* org, char* s)
{
    // Initialize a temporary pointer to traverse the linked list of organizations
    organization* temp = org;

    // Iterate through the linked list
    while (temp != NULL) {
        // Call the content search function for the current organization
        searchForContentByAnOrganization(temp, s);

        // Move to the next organization in the linked list
        temp = temp->next;
    }
}

void searchForContentByAnyNode()
{
    // Prompt the user to enter the content keyword to search for
    printf("Enter the content you want to search\n");

    // Declare a character array to store the user input
    char s[500];

    // Read the user input, allowing spaces in the input using %[^\n]s format specifier
    // Reading initial '\n' to address the 'enter' pressed after the input of the integer to call this function.
    // Otherwise, that 'enter' becomes the first '\n' for the scanf and no content is further taken except that first '\n'
    scanf("\n%[^\n]s", s);

    // Search for the entered content in individuals, groups, businesses, and organizations
    searchForContentByIndividuals(sn1->indi, s);
    searchForContentByGroups(sn1->grp, s);
    searchForContentByBusinesses(sn1->busi, s);
    searchForContentByOrganizations(sn1->org, s);
    //does not prompt anything if content not matched with any existing content
}

int main()
{
    sn1 = initNetwork();

    int in = 0, in2 = 0;
    int exitFlag = 0;

    do {
        printf("\n\nCREATE NEW ACCOUNT\nEnter 1 to add individual\t\t\tEnter 2 to add group\nEnter 3 to add business\t\t\t\tEnter 4 to add organization\n\nDIRECTORY\nEnter 5 to print all individuals\t\tEnter 6 to print all groups\nEnter 7 to print all businesses\t\t\tEnter 8 to print all organizations\nEnter 9 to print all users\n\nSEARCH USERS\nEnter 10 to search by type\t\t\tEnter 11 to search by name\nEnter 12 to search individuals by birthday\n\nLOGIN\nEnter 13 to login as individual\t\t\tEnter 14 to login as group\nEnter 15 to login as business\t\t\tEnter 16 to login as organization\n\nEnter 17 to Search Content\nEnter -1 to exit\n\n");

        if (scanf("%d", &in) != 1) {
            printf("Invalid input. Please enter a valid integer.\n\n");
            clearInputBuffer();
            continue;
        }
        switch (in) {
        case -1:
            printf("Do you want to exit?\nEnter 1 to exit\t\tEnter 0 to cancel\n\n");
            while (scanf("%d", &in2) != 1) {
                printf("Invalid input. Please enter a valid integer.\n\n");
                clearInputBuffer();
            }
            if (in2 == 1) {
                exitFlag = 1;
            }
            break;
        case 0:
            printf("Invalid input!\n\n");
            break;
        case 1:
            sn1->indi = initIndividual();
            break;
        case 2:
            sn1->grp = initGroup();
            break;
        case 3:
            sn1->busi = initBusiness();
            break;
        case 4:
            sn1->org = initOrganization();
            break;
        case 5:
            printIndividuals();
            break;
        case 6:
            printGroups();
            break;
        case 7:
            printBusinesses();
            break;
        case 8:
            printOrganizations();
            break;
        case 9:
            printIndividuals();
            printGroups();
            printBusinesses();
            printOrganizations();
            break;
        case 10:
            searchByType();
            break;
        case 11:
            searchByName();
            break;
        case 12:
            searchIndividualByBDay();
            break;
        case 13:
            goToIndividual();
            break;
        case 14:
            goToGroup();
            break;
        case 15:
            goToBusiness();
            break;
        case 16:
            goToOrganization();
            break;
        case 17:
            searchForContentByAnyNode();
            break;
        default:
            printf("Invalid input!\n\n");
            break;
        }

    } while (!exitFlag);

    return 0;
}
