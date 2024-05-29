/*
Social Network Implementation

This is a simple social network implementation in C, featuring individuals, groups, organizations, and businesses. The core entities (individual, group, organization, business) are represented as nodes in linked lists, and relationships between them are managed through various pointers.

Key Features:
- Individuals can be members of groups, organizations, and owners/customers of businesses.
- Groups can contain individuals and businesses as members.
- Organizations can have individuals as members.
- Businesses can have individuals as owners and customers.

Functionality:
- Creating and managing individuals, groups, organizations, and businesses.
- Establishing relationships between individuals, groups, organizations, and businesses.
- Printing/Searching information about entities and their relationships.
- Deleting entities and managing cascading deletions in relationships.
- Create/Search contents by different entities and related functionalities.
- Print all 1-hop linked nodes to a given input node.

File Structure:
- social.h: Header file containing structure definitions, function prototypes, and documentation.
- social.c: Implementation file containing the actual code for the social network operations.

Note:
- Please refer to the individual function comments for more detailed explanations.
*/

//structs
struct Coord2D;         //struct to store 2D-oordinates
struct Date;            //struct to store date
struct StringPL;        //String Pointer List or Linked List to store pointers to a string (char)
struct MandatoryInfo;   //store mandatory info common in all the 4 types of users
struct Individual;      //stores an individual user
struct Group;           //stores a group user
struct Business;        //stores a business user
struct Organization;    //stores an organization user
struct IndividualPL;    //Individual Pointer List or Linked List to store pointers to an individual struct
struct GroupPL;         //Group Pointer List or Linked List to store pointers to a group struct
struct BusinessPL;      //Business Pointer List or Linked List to store pointers to a business struct
struct OrganizationPL;  //Organization Pointer List or Linked List to store pointers to an individual struct
struct Network;         //a network comprising of linked lists of the 4 types of users

typedef struct Coord2D {
    float x;
    float y;
} coord2D;

typedef struct Date {
    int day;
    int month;
    int year;
} date;

typedef struct StringPL {
    char string[500];
    struct StringPL* next;
} stringPL;

typedef struct MandatoryInfo {
    int id;
    char name[50];
    time_t creationTime;
    // stringLL posts;
} mandatoryInfo;

typedef struct Individual {
    mandatoryInfo mandInfo;
    date bday;
    struct BusinessPL* ownerOf;
    struct BusinessPL* customerOf;
    struct GroupPL* inGroup;
    struct OrganizationPL* inOrganization;
    stringPL* content;
    struct Individual* next;
} individual;

typedef struct Group {
    mandatoryInfo mandInfo;
    struct IndividualPL* indiMemPL;
    struct BusinessPL* busiMemPL;  
    stringPL* content;
    struct Group* next;
} group;

typedef struct Business {
    mandatoryInfo mandInfo;
    coord2D loc;
    struct IndividualPL* ownerPL;
    struct IndividualPL* customerPL;
    struct GroupPL* inGroup;
    stringPL* content;
    struct Business* next;
} business;

typedef struct Organization {
    mandatoryInfo mandInfo;
    coord2D loc;
    struct IndividualPL* memberPL;
    stringPL* content;
    struct Organization* next;
} organization;

typedef struct IndividualPL {
    individual* indi;
    struct IndividualPL* next;
} individualPL;

typedef struct BusinessPL {
    business* busi;
    struct BusinessPL* next;
} businessPL;

typedef struct GroupPL {
    group* grp;
    struct GroupPL* next;
} groupPL;

typedef struct OrganizationPL {
    organization* org;
    struct OrganizationPL* next;
} organizationPL;

typedef struct Network {
    individual* indi;
    group* grp;
    business* busi;
    organization* org;
} network;
 

// Function prototypes

long long uniqueID();

date getDate();

coord2D getCoord2D();

int datecmp(date d1, date d2);

void printDate(date d);

void clearInputBuffer();
/*
Description:
Clears the input buffer by consuming any remaining characters in the buffer until a newline character or EOF is encountered.

Parameters:
None

Return Type:
None

Function Explanation:
- Uses a while loop to read characters from the input buffer until a newline character or EOF is encountered.
- Discards any characters read, effectively clearing the input buffer.
*/

individual* getIndividual(int id);
/*
Description:
Searches for an individual in the linked list by ID.

Parameters:
- id: ID of the individual to search for.

Return Type:
Pointer to the individual structure with the specified ID. Returns NULL if not found.

Function Explanation:
- Initializes a temporary individual structure (temp) and assigns the head of the existing list (sn1->indi) to it.
- Iterates through the existing list to find the individual with the specified ID.
- Returns a pointer to the individual structure if found, or NULL if not found.
*/

group* getGroup(int id);

business* getBusiness(int id);

organization* getOrganization(int id);

network* initNetwork();

mandatoryInfo initMandInfo();

individual* initIndividual();
/*
Description:
Initializes an individual structure and adds it to the linked list of individuals.

Return Type:
Pointer to the head of the updated linked list of individuals.

Function Explanation:
- Allocates memory for a new individual structure (indi).
- Initializes the mandatory information of the individual using initMandInfo function.
- Prompts the user to enter their birthday or skip the entry.
- If the user chooses to enter the birthday, calls getDate function to get the date.
- If the user chooses to skip, sets the day of the birthday to -1.
- Initializes other fields of the individual structure (customerOf, ownerOf, inGroup, inOrganization, content, next).
- Allocates memory for a temporary individual structure (temp) and assigns the head of the existing list (sn1->indi) to it.
- If the existing list is empty (temp is NULL), returns the new individual as the head of the list.
- Iterates through the existing list to find the end and appends the new individual to the end of the list.
*/

void printAnIndividualPL(individualPL* temp);

void printIndividualPLs(individualPL* temp);

void printAGroupPL(groupPL* temp);

void printGroupPLs(groupPL* temp);

void printABusinessPL(businessPL* temp);

void printBusinessPLs(businessPL* temp);

void printAnOrganizationPL(organizationPL* temp);

void printOrganizationPLs(organizationPL* temp);

void printAnIndividual(individual* temp);

void printIndividuals();

individualPL* initIndividualPL(individualPL* ipl, int id);

businessPL* initBusinessPL(businessPL* bpl, int id);
/*
Description:
Adds a business with the specified ID to the linked list of businessPL structures.

Parameters:
- bpl: Pointer to the existing linked list of businessPL structures.
- id: ID of the business to be added.

Return Type:
Pointer to the head of the updated linked list of businessPL structures.

Function Explanation:
- Allocates memory for a new businessPL node (busiPL).
- Retrieves the business with the specified ID using getBusiness function.
- If the business is not found, prints a message and returns the original head of the list.
- Initializes busiPL with the business and sets next to NULL.
- Allocates memory for a temporary businessPL node (temp) and assigns the head of the existing list (bpl) to it.
- If the existing list is empty (temp is NULL), returns the new node as the head of the list.
- Iterates through the existing list to check if the business with the entered ID already exists.
- If duplicate business is found, prints a message and returns the original head of the list.
- If no duplicate is found, appends the new node to the end of the list.
*/

group* initBusinessPLForGroup(group* grp);

group* initIndividualPLForGroup(group* grp);

business* initIndividualPLForBusinessOwner(business* busi);

business* initIndividualPLForBusinessCustomer(business* busi);

organization* initIndividualPLForOrganization(organization* org);
/*
Description:
Prompts the user to enter an individual ID to add to the organization and updates the organization's memberPL accordingly.

Parameters:
- org: Pointer to the organization to which an individual needs to be added.

Return Type:
Pointer to the updated organization.

Function Explanation:
- Prompts the user to enter an individual ID.
- Calls initIndividualPL to add the individual to the organization's memberPL.
- Retrieves the individual using getIndividual function.
- If the individual is not found, returns the organization without further modifications.
- Allocates memory for a new organizationPL node (opl).
- Initializes opl with the organization and sets next to NULL.
- Checks if the individual is already a member of the organization.
- If not, adds the organization to the individual's inOrganization linked list.
- Returns the updated organization.
*/

group* initGroup();
/*
Description:
Initializes a group and prompts the user for information such as mandatory info, members (individuals and businesses), and content.

Parameters:
None

Return Type:
Pointer to the head of the updated linked list of groups.

Function Explanation:
- Allocates memory for a new group (grp).
- Initializes mandatory information using initMandInfo function.
- Initializes indiMemPL, busiMemPL, content, and next fields of the group.
- Enters a loop to add individuals and businesses to the group.
- Asks the user to enter 1 to add an individual, 2 to add a business, or -1 to finish group creation.
- Calls initIndividualPLForGroup or initBusinessPLForGroup based on user input.
- Continues the loop until the user enters -1 to finish the group creation.
- Adds the created group to the linked list of groups.
*/

void printAGroup(group* temp);

void printGroups();

business* initBusiness();
/*
Description:
Initializes a business and prompts the user for information such as mandatory info, location, owners, customers, and groups.

Parameters:
None

Return Type:
Pointer to the head of the updated linked list of businesses.

Function Explanation:
- Allocates memory for a new business (busi).
- Initializes mandatory information using initMandInfo function.
- Prompts the user to enter the location using getCoord2D function.
- Initializes ownerPL, customerPL, inGroup, content, and next fields of the business.
- Enters a loop to add owners and customers to the business.
- Asks the user to enter 1 to add an owner, 2 to add a customer, or -1 to finish business creation.
- Calls initIndividualPLForBusinessOwner or initIndividualPLForBusinessCustomer based on user input.
- Continues the loop until the user enters -1 to finish the business creation.
- Adds the created business to the linked list of businesses.
*/

void printABusiness(business* temp);

void printBusinesses();

organization* initOrganization();
/*
Description:
Initializes an organization and prompts the user for information such as mandatory info, location, and members.

Parameters:
None

Return Type:
Pointer to the head of the updated linked list of organizations.

Function Explanation:
- Allocates memory for a new organization (org).
- Initializes mandatory information using initMandInfo function.
- Prompts the user to enter the location using getCoord2D function.
- Initializes memberPL, content, and next fields of the organization.
- Enters a loop to add members to the organization.
- Asks the user to enter 1 to add a member or -1 to finish organization creation.
- Calls initIndividualPLForOrganization to add a member if the user enters 1.
- Continues the loop until the user enters -1 to finish the organization creation.
- Adds the created organization to the linked list of organizations.
*/

void printAnOrganization(organization* temp);

void printOrganizations();

void searchByType();

int searchIndividualByName(char* s);

void searchIndividualByBDay();

int searchGroupByName(char* s);

int searchBusinessByName(char* s);

int searchOrganizationByName(char* s);

void searchByName();
/*
Description:
Searches for entities (individuals, groups, businesses, and organizations) by name
First '\n' is to handle the "Enter" pressed by the user to feed the previous input
Might not be good with spaces

Parameters:
None

Return Type:
Void
*/

void printIndividualsInAGroup( group* grp);

void printIndividualsInGroups(groupPL* temp);

void printBusinessesInAGroup( group* grp);

void printBusinessesInGroups(groupPL* temp);

void printIndividualsInABusiness(business* busi);

void printIndividualsInBusinesses(businessPL* temp);

void printIndividualsInAnOrganization( organization* org);

void printIndividualsInOrganizations(organizationPL* temp);


void printLinksInAnIndividual(individual* indi);
/*
Description:
Prints information about the links of an individual, including groups, businesses (as owner and customer), and organizations.

Parameters:
- indi: Pointer to the individual structure for which links are to be printed.

Return Type:
Void
*/

void printLinksInIndividuals(individualPL* temp);
/*
Description:
Prints information about linked individuals in a given linked list of individual structures.

Parameters:
- temp: Pointer to the head of the linked list of individual structures.

Return Type:
Void
*/

void printIndividuals1Hop(individual* indi);
/*
Description:
Prints information about individuals, businesses, and organizations associated with a given individual.

Parameters:
- indi: Pointer to the individual structure.

Return Type:
Void
*/

void printGroups1Hop(group* grp);
/*
Description:
Prints the links of member individuals and member businesses associated with a given group.

Parameters:
- grp: Pointer to the group structure.

Return Type:
Void
*/

void printBusinesses1Hop(business* busi);
/*
Description:
Prints the links of owners and customers associated with a given business.

Parameters:
- busi: Pointer to the business structure.

Return Type:
Void
*/

void printOrganizations1Hop(organization* org);
/*
Description:
Prints the links of member individuals in a given organization.

Parameters:
- org: Pointer to the organization structure.

Return Type:
Void
*/

void deleteIndividualFromIndividualPL(int id, individualPL** iplPtr);
/*
Description:
Deletes an individual node from a linked list of individual nodes.

Parameters:
- id: ID of the individual to be deleted.
- iplPtr: Pointer to the head of the linked list of individual nodes.

Return Type:
Void
*/

void deleteIndividualFromGroups(individual* indi);
/*
Description:
Deletes an individual from the list of groups where the individual is a member.

Parameters:
- indi: Pointer to the individual node to be deleted.

Return Type:
Void
*/

void deleteIndividualFromBusinessesAsOwner(individual* indi);
/*
Description:
Deletes an individual from the list of businesses where the individual is an owner.

Parameters:
- indi: Pointer to the individual node to be deleted.

Return Type:
Void
*/

void deleteIndividualFromBusinessesAsCustomer(individual* indi);
/*
Description:
Deletes an individual from the list of businesses where the individual is a customer.

Parameters:
- indi: Pointer to the individual node to be deleted.

Return Type:
Void
*/

void deleteIndividualFromOrganizations(individual* indi);
/*
Description:
Deletes an individual from the list of organizations the individual is a member of.

Parameters:
- indi: Pointer to the individual node to be deleted.

Return Type:
Void
*/

void deleteIndividualSelf(int id);
/*
Description:
Deletes an individual node from the linked list of individuals.

Parameters:
- id: ID of the individual node to be deleted.

Return Type:
Void

Function Explanation:
- Searches for the individual node with the given ID in the linked list.
- If the head node itself holds the key to be deleted:
  - Changes the head of the list to the next node.
  - Frees the memory of the old head node.
- If the key is not in the head node:
  - Searches for the key in the linked list while keeping track of the previous node.
  - Unlinks the node from the linked list.
  - Frees the memory of the node to be deleted.

Note: The actual implementation of functions such as printf and free is assumed to be available in the standard C library.
*/

void deleteIndividual(individual* indi);
/*
Description:
Deletes an individual node from the linked list of individuals.

Parameters:
- indi: Pointer to the individual node to be deleted.

Return Type:
Void
*/

void deleteGroupFromGroupPL(int id, groupPL** gplPtr);
/*
Description:
Deletes the group node from the linked list of groupPL structures.

Parameters:
- id: ID of the group to be deleted.
- gplPtr: Pointer to the head of the linked list of groupPL structures.

Return Type:
Void
*/

void deleteGroupFromIndividuals(group* grp);
/*
Description:
Deletes the group node from the linked lists of individuals to which its members belong.

Parameters:
- grp: Pointer to the group to be deleted.

Return Type:
Void
*/

void deleteGroupFromBusinesses(group* grp);
/*
Description:
Removes references to the group from linked businesses.

Parameters:
- grp: Pointer to the group node.

Return Type:
Void
*/

void deleteGroupSelf(int id);
/*
Description:
Deletes the group node with the specified ID from the linked list of groups.

Parameters:
- id: ID of the group to be deleted.

Return Type:
Void
*/

void deleteGroup(group* grp);
/*
Description:
Deletes a group node, removing its references from individuals and businesses, and then frees the memory.

Parameters:
- grp: Pointer to the group node to be deleted.

Return Type:
Void
*/

void deleteBusinessFromBusinessPL(int id, businessPL** bplPtr);
/*
Description:
Deletes a business node from the linked list of businessPL structures based on the provided ID.

Parameters:
- id: The ID of the business node to be deleted.
- bplPtr: Pointer to the head pointer of the linked list of businessPL structures.

Return Type:
Void
*/

void deleteBusinessFromIndividualsOwners(business* busi);
/*
Description:
Removes references to a business from linked individuals who are owners.

Parameters:
- busi: Pointer to the business structure whose references are to be removed.

Return Type:
Void
*/
void deleteBusinessFromIndividualsCustomers(business* busi);
/*
Description:
Removes references to a business from linked individuals who are customers.

Parameters:
- busi: Pointer to the business structure whose references are to be removed.

Return Type:
Void
*/

void deleteBusinessFromGroups(business* busi);
/*
Description:
Removes references to a business from linked groups.

Parameters:
- busi: Pointer to the business structure whose references are to be removed.

Return Type:
Void
*/

void deleteBusinessSelf(int id);
/*
Description:
Deletes a business node from the linked list of businesses based on the provided ID.

Parameters:
- id: The ID of the business node to be deleted.

Return Type:
Void
*/

void deleteBusiness(business* busi);
/*
Description:
Deletes a business and removes references to it from linked groups, business owners, and business customers.

Parameters:
- busi: Pointer to the business structure to be deleted.

Return Type:
Void

Function Explanation:
- Calls the deleteBusinessFromGroups function to remove references to the business from linked groups.
- Calls the deleteBusinessFromIndividualsOwners function to remove references to the business from linked business owners.
- Calls the deleteBusinessFromIndividualsCustomers function to remove references to the business from linked business customers.
- Calls the deleteBusinessSelf function to perform the self-deletion of the business.
*/

void deleteOrganizationFromOrganizationPL(int id, organizationPL** oplPtr);

void deleteOrganizationFromIndividuals(organization* org);
/*
Description:
Removes references to an organization from linked individuals.

Parameters:
- org: Pointer to the organization structure for which references are to be removed.

Return Type:
Void

Function Explanation:
- Iterates through the linked list of individuals associated with the organization (org).
- Calls the deleteOrganizationFromOrganizationPL function for each individual to remove the organization reference from their organization pointer.
*/

void deleteOrganizationSelf(int id);

void deleteOrganization(organization* org);
/*
Description:
Deletes an organization, removing its references from individuals and then deleting the organization itself.

Parameters:
- org: Pointer to the organization structure to be deleted.

Return Type:
Void

Function Explanation:
- Calls the deleteOrganizationFromIndividuals function to remove references to the organization from linked individuals.
- Calls the deleteOrganizationSelf function to delete the organization itself.
*/

stringPL* initStringPL(stringPL* spl);
/*
Description:
Initializes a stringPL node and adds it to the linked list of stringPL structures.

Parameters:
- spl: Pointer to the existing linked list of stringPL structures.

Return Type:
- Pointer to the head of the updated linked list of stringPL structures.

Function Explanation:
- Allocates memory for a new stringPL node (strPL).
- Reads a string from the user and assigns it to the string field of the new node.
- Initializes the next pointer of the new node to NULL.
- Allocates memory for a temporary stringPL node (temp) and assigns the head of the existing list (spl) to it.
- If the existing list is empty (temp is NULL), returns the new node as the head of the list.
- Iterates through the existing list to check if the entered content already exists.
- If duplicate content is found, prints a message and returns the original head of the list.
- If no duplicate is found, appends the new node to the end of the list.
*/

void printContentsByAnIndividual(individual* indi);
/*
Description:
Prints content posted by the specified individual.

Parameters:
- indi: Pointer to the individual structure.

Return Type:
Void

Function Explanation:
- Initializes a temporary pointer to the stringPL structure using the individual pointer (indi).
- Iterates through the content of the individual.
  - Prints each content item along with the name of the individual.
- Continues until all content items are processed.
*/

void printContentByIndividualsMembersOfOrganizationPL(organizationPL* opl);
/*
Description:
Prints content posted by individuals who are members of the specified organization.

Parameters:
- opl: Pointer to the organizationPL structure.

Return Type:
Void

Function Explanation:
- Initializes a temporary pointer to the individualPL structure using the organizationPL pointer (opl).
- Iterates through the individual members of the organization.
  - Calls printContentsByAnIndividual for each individual to print their content.
- Continues until all organization members are processed.
*/

void printContentByIndividualsMembersOfGroupPL(groupPL* gpl);
/*
Description:
Prints content posted by individuals who are members of the specified group.

Parameters:
- gpl: Pointer to the groupPL structure.

Return Type:
Void

Function Explanation:
- Initializes a temporary pointer to the individualPL structure using the groupPL pointer (gpl).
- Iterates through the individual members of the group.
  - Calls printContentsByAnIndividual for each individual to print their content.
- Continues until all group members are processed.
*/

void printContentByIndividuals2LinkedToIndividual(individual* indi);
/*
Description:
Prints content posted by individuals linked to the specified individual through group or organization memberships.

Parameters:
- indi: Pointer to the individual.

Return Type:
Void

Function Explanation:
- Checks if the individual is a member of any group (indi->inGroup is not NULL).
  - If true, calls printContentByIndividualsMembersOfGroupPL with the group pointer (indi->inGroup).
- Checks if the individual is a member of any organization (indi->inOrganization is not NULL).
  - If true, calls printContentByIndividualsMembersOfOrganizationPL with the organization pointer (indi->inOrganization).
*/

void goToIndividual();
/*
Description:
This function allows a user to log in as an individual, providing a menu with various options for the individual's account.

Parameters:
None

Return Type:
Void

Function Explanation:

User Input: The function prompts the user to enter the ID of their individual account for login.

Validation: It ensures that the user input is a valid integer; if not, it prompts the user again until a valid input is provided.

Login Attempt: Retrieves the individual information based on the entered ID using the getIndividual function.

Account Not Found: If the individual is not found (NULL), it displays a message and exits the function.

Menu Options:
1. Add/Change Birthday: Allows the individual to add or change their birthday.
2. Post Content: Enables the individual to post content.
3. Print 1-hop Linked Nodes: Prints all 1-hop linked nodes for the individual.
4. Print Content by Linked Individuals: Prints content posted by individuals linked to the current individual.
5. Delete Account: Deletes the individual's account.
-1. Exit: Exits the function.

User Menu: The function displays a menu, and the user can choose options by entering the corresponding numbers.

User Input Validation: Ensures that the user's input for the menu is a valid integer.

Menu Switch: Executes the selected option based on the entered number.

Exit Condition: Continues the menu loop until the user chooses to exit (-1) or cancels an exit operation.

Deletion Confirmation: For options involving deletion, the function asks for confirmation before proceeding.

Exit Confirmation: If the user chooses to exit, the function asks for confirmation before proceeding.

Exit Flag: The function uses an exitFlag to track whether the user has chosen to exit.

Add/Change Birthday: If the individual has no birthday, it adds one; otherwise, it changes the existing one.

Delete Account: If the user confirms, the function calls the deleteIndividual function and exits.

Return: Returns to the main menu or exits the function based on the user's choice.
*/

void goToGroup();
/*
Description:
This function allows a user to log in as a group, providing a menu with various options for the group's account.

Parameters:
None

Return Type:
Void

Function Explanation:

User Input: The function prompts the user to enter the ID of their group account for login.

Validation: It ensures that the user input is a valid integer; if not, it prompts the user again until a valid input is provided.

Login Attempt: Retrieves the group information based on the entered ID using the getGroup function.

Account Not Found: If the group is not found (NULL), it displays a message and exits the function.

Menu Options:
1. Post Content: Enables the group to post content.
2. Print 1-hop Linked Nodes: Prints all 1-hop linked nodes for the group.
3. Add Individual: Adds an individual to the group.
4. Add Business: Adds a business to the group.
5. Delete Account: Deletes the group's account.
-1. Exit: Exits the function.

User Menu: The function displays a menu, and the user can choose options by entering the corresponding numbers.

User Input Validation: Ensures that the user's input for the menu is a valid integer.

Menu Switch: Executes the selected option based on the entered number.

Exit Condition: Continues the menu loop until the user chooses to exit (-1) or cancels an exit operation.

Deletion Confirmation: For options involving deletion, the function asks for confirmation before proceeding.

Exit Confirmation: If the user chooses to exit, the function asks for confirmation before proceeding.

Exit Flag: The function uses an exitFlag to track whether the user has chosen to exit.

Delete Account: If the user confirms, the function calls the deleteGroup function and exits.

Return: Returns to the main menu or exits the function based on the user's choice.
*/

void goToBusiness();
/*
Description:
This function allows a user to log in as a business, providing a menu with various options for the business's account.

Parameters:
None

Return Type:
Void

Function Explanation:

User Input: The function prompts the user to enter the ID of their business account for login.

Validation: It ensures that the user input is a valid integer; if not, it prompts the user again until a valid input is provided.

Login Attempt: Retrieves the business information based on the entered ID using the getBusiness function.

Account Not Found: If the business is not found (NULL), it displays a message and exits the function.

Menu Options:
1. Change Location: Allows the business to update its location information (coordinates).
2. Post Content: Enables the business to post content.
3. Print 1-hop Linked Nodes: Prints all 1-hop linked nodes for the business.
4. Add Owner: Adds an individual as an owner to the business.
5. Add Customer: Adds an individual as a customer to the business.
6. Delete Account: Deletes the business's account.
-1. Exit: Exits the function.

User Menu: The function displays a menu, and the user can choose options by entering the corresponding numbers.

User Input Validation: Ensures that the user's input for the menu is a valid integer.

Menu Switch: Executes the selected option based on the entered number.

Exit Condition: Continues the menu loop until the user chooses to exit (-1).

Deletion Confirmation: For options involving deletion, the function asks for confirmation before proceeding.

Delete Account: If the user confirms, the function calls the deleteBusiness function and exits.

Cancel Deletion: If the user cancels, a corresponding message is displayed, and the function continues.

Exit Flag: The exitFlag is used to track the exit condition of the loop.

Return: Returns to the main menu or exits the function based on the user's choice.
*/

void goToOrganization();
/*
Description:
This function allows a user to log in as an organization, providing a menu with various options for the organization's account.

Parameters:
None

Return Type:
Void

Function Explanation:

User Input: The function prompts the user to enter the ID of their organization account for login.

Validation: It ensures that the user input is a valid integer; if not, it prompts the user again until a valid input is provided.

Login Attempt: Retrieves the organization information based on the entered ID using the getOrganization function.

Account Not Found: If the organization is not found (NULL), it displays a message and exits the function.

Menu Options:
1. Change Location: Allows the organization to update its location information (coordinates).
2. Post Content: Enables the organization to post content.
3. Print 1-hop Linked Nodes: Prints all 1-hop linked nodes for the organization.
4. Add Individual: Adds an individual to the organization.
5. Delete Account: Deletes the organization's account.
-1. Exit: Exits the function.

User Menu: The function displays a menu, and the user can choose options by entering the corresponding numbers.

User Input Validation: Ensures that the user's input for the menu is a valid integer.

Menu Switch: Executes the selected option based on the entered number.

Exit Condition: Continues the menu loop until the user chooses to exit (-1).

Return: Returns to the main menu or exits the function based on the user's choice.
*/

void searchForContentByAGroup(group* grp, char* s);
/*
Searches for a specific content string within a group's content and prints a message if found.

Parameters:
- group* grp: Group to search within.
- char* s: Content keyword to search for.

Return Type:
Void
*/

void searchForContentByGroups(group* grp, char* s);
/*
Iterates through groups and calls searchForContentByAGroup for each group.

Parameters:
- group* grp: Head of the group list.
- char* s: Content keyword to search for.

Return Type:
Void
*/

void searchForContentByABusiness(business* busi, char* s);
/*
Searches for a specific content string within a business's content and prints a message if found.

Parameters:
- business* busi: Business to search within.
- char* s: Content keyword to search for.

Return Type:
Void
*/

void searchForContentByBusinesses(business* busi, char* s);
/*
Iterates through businesses and calls searchForContentByABusiness for each business.

Parameters:
- business* busi: Head of the business list.
- char* s: Content keyword to search for.

Return Type:
Void
*/

void searchForContentByAnOrganization(organization* org, char* s);
/*
Searches for a specific content string within an organization's content and prints a message if found.

Parameters:
- organization* org: Organization to search within.
- char* s: Content keyword to search for.

Return Type:
Void
*/

void searchForContentByOrganizations(organization* org, char* s);
/*
Iterates through organizations and calls searchForContentByAnOrganization for each organization.

Parameters:
- organization* org: Head of the organization list.
- char* s: Content keyword to search for.

Return Type:
Void
*/

void searchForContentByAnIndividual(individual* indi, char* s);
/*
Searches for a specific content string within an individual's content and prints a message if found.

Parameters:
- individual* indi: Individual to search within.
- char* s: Content keyword to search for.

Return Type:
Void
*/

void searchForContentByIndividuals(individual* indi, char* s);
/*
Iterates through individuals and calls searchForContentByAnIndividual for each individual.

Parameters:
- individual* indi: Head of the individual list.
- char* s: Content keyword to search for.

Return Type:
Void
*/

void searchForContentByAnyNode();
/*
Allows the user to search for content with a specific keyword across individuals, groups, businesses, and organizations.

Parameters:
None

Return Type:
Void
*/


/*

Sample input to create nodes and links:

1
a b s d
-1
1
b b s d
-1
1
c b s d
-1
3
a b s d
1
1
1
0
1
1
1
2
2
0
2
1
2
2
-1
3
b b s d
1
1
1
0
1
1
1
2
2
0
2
1
2
2
-1
3
c b s d
1
1
1
0
1
1
1
2
2
0
2
1
2
2
-1
2
a b s d
1
0
1
1
1
2
2
3
2
4
2
5
-1
2
b b s d
1
0
1
1
1
2
2
3
2
4
2
5
-1
2
c b s d
1
0
1
1
1
2
2
3
2
4
2
5
-1
4
a b s d
1
1
1
0
1
1
1
2
-1
4
b b s d
1
1
1
1
1
2
1
0
-1
4
c b s d
1
1
1
0
1
1
1
2
-1

*/