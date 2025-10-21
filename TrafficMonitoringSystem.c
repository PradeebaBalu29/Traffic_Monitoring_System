#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct RoadSegment {
    char name[50];
    int incoming;
    int outgoing;
    struct RoadSegment* left;
    struct RoadSegment* right;
} RoadSegment;

RoadSegment* createNode(char* name, int incoming, int outgoing) {
    RoadSegment* newNode = (RoadSegment*)malloc(sizeof(RoadSegment));
    strcpy(newNode->name, name);
    newNode->incoming = incoming;
    newNode->outgoing = outgoing;
    newNode->left = newNode->right = NULL;
    return newNode;
}

RoadSegment* insertRoadSegment(RoadSegment* root, char* name, int incoming, int outgoing) {
    if (root == NULL) {
        return createNode(name, incoming, outgoing);
    }
    if (strcmp(name, root->name) < 0) {
        root->left = insertRoadSegment(root->left, name, incoming, outgoing);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insertRoadSegment(root->right, name, incoming, outgoing);
    }
    return root;
}

void updateTraffic(RoadSegment* root, char* name, int incoming, int outgoing) {
    if (root == NULL) {
        printf("Road segment not found.\n");
        return;
    }
    if (strcmp(name, root->name) < 0) {
        updateTraffic(root->left, name, incoming, outgoing);
    } else if (strcmp(name, root->name) > 0) {
        updateTraffic(root->right, name, incoming, outgoing);
    } else {
        root->incoming = incoming;
        root->outgoing = outgoing;
        printf("Traffic updated for %s: Incoming = %d, Outgoing = %d\n", name, incoming, outgoing);
    }
}

void printTrafficDetails(RoadSegment* root) {
    if (root != NULL) {
        printTrafficDetails(root->left);
        printf("Road: %s, Incoming: %d, Outgoing: %d\n", root->name, root->incoming, root->outgoing);
        printTrafficDetails(root->right);
    }
}

void suggestAlternativeRoutes(RoadSegment* root) {
    if (root != NULL) {
        suggestAlternativeRoutes(root->left);
        if (root->incoming > 10) { 
            printf("Heavy traffic on %s. Consider alternative routes.\n", root->name);
        }
        suggestAlternativeRoutes(root->right);
    }
}

int main() {
    RoadSegment* root = NULL;

    root = insertRoadSegment(root, "A-Street", 5, 3);
    root = insertRoadSegment(root, "B-Street", 15, 8);
    root = insertRoadSegment(root, "C-Street", 2, 4);

    printf("Initial traffic details:\n");
    printTrafficDetails(root);

    updateTraffic(root, "A-Street", 6, 3);
    updateTraffic(root, "B-Street", 20, 9);

    printf("\nUpdated traffic details:\n");
    printTrafficDetails(root);

    printf("\nAlternative routes suggestion:\n");
    suggestAlternativeRoutes(root);

    return 0;
}
