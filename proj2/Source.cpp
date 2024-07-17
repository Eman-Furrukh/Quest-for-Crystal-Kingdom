#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include "windows.h" 
using namespace std;

// global variables
int ROWS = 20;
int COLS = 20;
const int ROWS1 = 20;
const int COLS1 = 20;
int Score = 0;
const int N = 20;
static int index[2];
int customLocation[2] = { 4,4 };

// Prints the 2D array which consists of games map
void printMatrix(char** matrix) {

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Updates the score after every move unless youre on a clear path
void ScoreUpdate(char str)
{
    if (str == '#') {
        Score = Score - 5;
    }
    else if (str == 'J' || str == 'j') {
        Score = Score + 50;
    }
    else if (str == '@') {
        Score = Score - 30;
    }
    else if (str == '$') {
        Score = Score - 70;
    }
    else if (str == '&') {
        Score = Score - 50;
    }
    else if (str == 'W' || str == 'w') {
        Score = Score + 30;
    }
    else if (str == 'P' || str == 'p') {
        Score = Score + 70;
    }
}

// Creates adjacent matrix based off the 2D array made previously
int** createAdjMatrix(char** arr, int n) {
    int** adjMatrix = new int* [n];
    for (int i = 0; i < n; i++) {
        adjMatrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == '#') {
                adjMatrix[i][j] = 100;
            }
            else {
                adjMatrix[i][j] = 1;
            }
        }
    }
    return adjMatrix;
}

// Prints adjacent matrix
void printAdjMatrix(int** adjMatrix, int n) {
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Floyds algorthim from (0,0)
void floyd(int** graph, const int numVertices, int startX, int startY, int endX, int endY) {
    int dist[ROWS1][ROWS1] = { 0 };
    int i, j, k;
    int movement = 0;

    // Initialize the distance matrix
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Calculate shortest path for all pairs of vertices
    for (k = 0; k < numVertices; k++) {
        for (i = 0; i < numVertices; i++) {
            for (j = 0; j < numVertices; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    movement++;
                }
            }
        }
    }



    // Print shortest path from start to end vertex
    //cout << "Floyds Algorthm \nShortest path from (" << startX << "," << startY << ") to (" << endX << "," << endY << ") is: " << dist[startX][startY] + dist[endX][endY] << endl;
    std::cout << "Floyds Algorthm \nShortest path from (" << startX << "," << startY << ") to (" << endX << "," << endY << ") number of movement needed  " << movement;
}

// Floyds algorithm from custom location
void floydCustom(int** graph, int n, int start_row, int start_col, int end_row, int end_col) {
    // Initialize distance matrix with initial graph values
    int** dist = new int* [n];
    //path to store number of movement 
    int distance = 0;
    for (int i = 0; i < n; i++) {
        dist[i] = new int[n];
        for (int j = 0; j < n; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Update distance matrix with shortest path through k
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    distance++;

                }
            }
        }
    }


    // Print shortest distance from start index to end index
   // cout << "\nFloyds Algortihm\nShortest distance from custom location i.e., (" << start_row << ", " << start_col << ") to (" << end_row << ", " << end_col << "): " << dist[start_row][start_col] + dist[start_col][end_row] + dist[end_row][end_col] << endl;

    cout << "\nFloyds Algortihm\nShortest distance from custom location i.e., (" << start_row << ", " << start_col << ") to (" << end_row << ", " << end_col << ") shortest path to Crystal have  " << distance << " movement " << endl;


}

// Finds the index of the asterisk on the map and returns it
int* findAsterisk(char** map, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == '*') {
                index[0] = i;
                index[1] = j;
                return index;
            }
        }
    }
    return NULL;
}

// Function to find the vertex with minimum distance value
int minDistance(int dist[], bool visited[], int n) {
    int minDist = INT_MAX, minIndex;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] <= minDist) {
            minDist = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra(int** adjMatrix, int start, int end, int n) {
    int dist[ROWS1];
    bool visited[ROWS1];

    // Initialize all distances as infinite and visited array as false
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        // Find the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, visited, n);

        // Mark the selected vertex as visited
        visited[u] = true;

        // Update the distance of the adjacent vertices of the selected vertex
        for (int v = 0; v < n; v++) {
            if (!visited[v] && adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
            }
        }
    }

    // Print the shortest distance to end vertex
    cout << "Dijkstra Algorithm\nShortest distance from (0,0) to end vertex: " << dist[end] << endl;
}

// Function to find the shortest path using Dijkstra's algorithm 
void dijkstraCustom(int** adjMatrix, int n, int startX, int startY) {
    int dist[ROWS1];
    bool visited[ROWS1];

    for (int i = 0; i < n; i++) {

        dist[i] = INT_MAX;
        visited[i] = false;

    }

    dist[startX * n + startY] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = minDistance(dist, visited, n);
        visited[u] = true;

        int row = u / n;
        int col = u % n;

        for (int v = 0; v < n * n; v++) {
            int row_v = v / n;
            int col_v = v % n;

            if (adjMatrix[u][v] && !visited[v] && dist[u] != INT_MAX
                && dist[u] + adjMatrix[u][v] < dist[row_v * n + col_v]) {
                dist[row_v * n + col_v] = dist[u] + adjMatrix[u][v];
            }
        }
    }
    // Count the number of vertices that can be reached from the starting vertex
    int count = 0;
    for (int i = 0; i < n * n; i++) {
        if (dist[i] != INT_MAX) {
            count++;
        }
    }
    cout << "Dijkstras Algortihm\nNumber of reachable vertices from (" << startX << ", " << startY << "): " << count << endl;
}


// Kruskal's algorithm to find the minimum spanning tree of the map
void kruskal(int** adjMatrix, int n) {
    // Create an array of edges and initialize it
    int edges[ROWS1 * ROWS1][3];
    int edgeIndex = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adjMatrix[i][j] != 0) {
                edges[edgeIndex][0] = i;
                edges[edgeIndex][1] = j;
                edges[edgeIndex][2] = adjMatrix[i][j];
                edgeIndex++;
            }
        }
    }

    // Sort the edges in ascending order based on weight
    for (int i = 0; i < edgeIndex - 1; i++) {
        for (int j = 0; j < edgeIndex - i - 1; j++) {
            if (edges[j][2] > edges[j + 1][2]) {
                int temp[3];
                temp[0] = edges[j][0];
                temp[1] = edges[j][1];
                temp[2] = edges[j][2];
                edges[j][0] = edges[j + 1][0];
                edges[j][1] = edges[j + 1][1];
                edges[j][2] = edges[j + 1][2];
                edges[j + 1][0] = temp[0];
                edges[j + 1][1] = temp[1];
                edges[j + 1][2] = temp[2];
            }
        }
    }

    // Create an array to keep track of visited nodes and initialize it
    int visited[ROWS1];
    for (int i = 0; i < n; i++) {
        visited[i] = i;
    }

    // Create an array to store the minimum spanning tree and initialize it
    int tree[ROWS1 - 1][2];
    int treeIndex = 0;

    // Iterate over the edges and add them to the minimum spanning tree
    for (int i = 0; i < edgeIndex; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2];

        // Check if adding the edge creates a cycle
        if (visited[u] != visited[v]) {
            tree[treeIndex][0] = u;
            tree[treeIndex][1] = v;
            treeIndex++;

            // Merge the visited nodes into a single set
            int oldID = visited[u];
            int newID = visited[v];
            for (int j = 0; j < n; j++) {
                if (visited[j] == oldID) {
                    visited[j] = newID;
                }
            }
        }
    }

    // Print the minimum spanning tree
    cout << "Khruskals Algorithm\nMinimum Spanning Tree:" << endl;
    for (int i = 0; i < n - 1; i++) {
        cout << "(" << tree[i][0] << ", " << tree[i][1] << ")" << "   ";
    }
    cout << endl;
}

// Prim's algorithm to find minimum spanning tree of the map
void prim(int** adjMatrix, int n) {
    // Initialize arrays to track visited and minimum edges
    bool visited[ROWS1];
    int minEdge[ROWS1], minIndex[ROWS1];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        minEdge[i] = INT_MAX;
        minIndex[i] = -1;
    }

    // Start from vertex 0
    minEdge[0] = 0;
    for (int i = 0; i < n - 1; i++) {
        // Find vertex with minimum edge value
        int minVertex = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (minVertex == -1 || minEdge[j] < minEdge[minVertex])) {
                minVertex = j;
            }
        }

        // Mark vertex as visited
        visited[minVertex] = true;

        // Update minimum edge values for adjacent vertices
        for (int j = 0; j < n; j++) {
            if (adjMatrix[minVertex][j] && !visited[j] && adjMatrix[minVertex][j] < minEdge[j]) {
                minEdge[j] = adjMatrix[minVertex][j];
                minIndex[j] = minVertex;
            }
        }
    }

    // Print the minimum spanning tree
    cout << "Prims Algorithm\nMinimum Spanning Tree:" << endl;
    for (int i = 1; i < n; i++) {
        cout << minIndex[i] << "-" << i << ": " << adjMatrix[i][minIndex[i]] << "   ";
    }
    cout << endl;
}

// Finds shortest path 
void findShortestPath(char** map, int n) {
    int* asteriskIndex = findAsterisk(map, n);
    if (asteriskIndex == NULL) {
        cout << "Error: Asterisk not found." << endl;
        return;
    }
    int path[ROWS1][ROWS1];
    int** am = createAdjMatrix(map, N);
    // Calculate the shortest path from the asterisk to (0,0)
    floyd(am, ROWS1, 0, 0, asteriskIndex[0], asteriskIndex[1]);
    // Calculate the shortest path from the asterisk to a custom location
    floydCustom(am, n, asteriskIndex[0], asteriskIndex[1], customLocation[0], customLocation[1]);
    // Calculate the shortest path from the asterisk to (0,0)
    dijkstra(am, 0, index[0], N);
    // Calculate the shortest path from the asterisk to a custom location
    dijkstraCustom(am, n, customLocation[0], customLocation[1]);
    // Find the minimum spanning tree of the map using Kruskal's algorithm
    kruskal(am, n);
    // Find the minimum spanning tree of the map using Prim's algorithm
    prim(am, n);
    // int shortestPath = path[0][asteriskIndex[0]] + path[1][asteriskIndex[1]];
     //cout << "\nThe shortest path to the asterisk is: " << shortestPath << endl;

}

// Class of Node which consists of default and
// parameterised constructor
class Node {
public:
    int id;
    int reward_score;
    int count;
    Node* left;
    Node* right;
    int height;
    Node() {
        id = 0;
        reward_score = 0;
        count = 0;
        left = NULL;
        right = NULL;
        height = 0;
    }
    Node(int id, int reward_score) {
        this->id = id;
        this->reward_score = reward_score;
        this->count = 1;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }
};

// Class of AVL Tree 
class AVLTree {
public:
    AVLTree() {
        root = NULL;
        srand(time(NULL));
    }

    AVLTree(Node* node)
    {
        root = node;
    }

    int height(Node* node) {
        if (node == NULL) {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(Node* node) {
        if (node == NULL) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, int reward_score) {
        if (node == NULL) {
            int id;
            if (root == NULL) {
                id = 100;
            }
            else {
                id = rand() % 201; // generates a random id from 0 to 200 (inclusive)
            }
            root = new Node(id, reward_score);
            return root;
        }
        if (reward_score < node->reward_score) {
            node->left = insert(node->left, reward_score);
        }
        else if (reward_score > node->reward_score) {
            node->right = insert(node->right, reward_score);
        }
        else {
            node->count++;
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        int bf = balanceFactor(node);

        if (bf > 1 && reward_score < node->left->reward_score) {
            return rightRotate(node);
        }
        if (bf < -1 && reward_score > node->right->reward_score) {
            return leftRotate(node);
        }
        if (bf > 1 && reward_score > node->left->reward_score) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (bf < -1 && reward_score < node->right->reward_score) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* node, int reward_score) {
        if (node == NULL) {
            return node;
        }
        if (reward_score < node->reward_score) {
            node->left = deleteNode(node->left, reward_score);
        }
        else if (reward_score > node->reward_score) {
            node->right = deleteNode(node->right, reward_score);
        }
        else {
            if (node->count > 1) {
                node->count--;
                return node;
            }
            if (node->left == NULL || node->right == NULL) {
                Node* temp = node->left ? node->left : node->right;

                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else {
                Node* temp = minValueNode(node->right);

                node->id = temp->id;
                node->reward_score = temp->reward_score;
                node->count = temp->count;

                node->right = deleteNode(node->right, temp->reward_score);
            }
        }

        if (node == NULL) {
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        int bf = balanceFactor(node);

        if (bf > 1 && balanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }
        if (bf > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (bf < -1 && balanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        if (bf < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void insert(int reward_score) {
        root = insert(root, reward_score);
    }

    void remove(int reward_score) {
        root = deleteNode(root, reward_score);
    }

    void inorder(Node* node) {
        if (node == NULL) {
            return;
        }
        inorder(node->left);
        for (int i = 0; i < node->count; i++) {
            cout << "Item ID: " << node->id << ", Score: " << node->reward_score << endl;
        }
        inorder(node->right);
    }

    void displayInventory() {
        cout << "Player Inventory: " << endl;
        inorder(root);
    }

private:
    Node* root;
};

// Prints animation after you've won the game
void printWonAnimation() {
    system("cls"); // Clear the terminal screen
    system("Color 20");
    std::cout << std::endl;
    std::cout << "\t\t  .--. " << std::endl;
    std::cout << "\t\t /.-. '----------." << std::endl;
    std::cout << "\t\t \\o \\_____/      \\__" << std::endl;
    std::cout << "\t\t /\\   /\\             )" << std::endl;
    std::cout << "\t\t(__\\ /__)(__\\_______)" << std::endl;
    std::cout << std::endl;
    std::cout << "\t\tCongratulations," << std::endl;
    std::cout << "\t\t     you won!" << std::endl;
    std::cout << "\t\t your total score is: " << Score << endl;
    std::cout << std::endl;
    std::cout << "\t\t  .--. " << std::endl;
    std::cout << "\t\t /.-. '----------." << std::endl;
    std::cout << "\t\t \\o \\_____/      \\__" << std::endl;
    std::cout << "\t\t /\\   /\\             )" << std::endl;
    std::cout << "\t\t(__\\ /__)(__\\_______)" << std::endl;
}

// Prints animation after you've lost the game
void printLoseAnimation() {
    system("cls"); // Clear the terminal screen
    system("Color 40");
    cout << "\t\t\t  _____              __   __  ______   ____ __       _ _____  _____  " << endl;
    cout << "\t\t\t / ____|    / \\    | \\/    |  ____| / __ \\ \\    / /  ____|  __ \\ " << endl;
    cout << "\t\t\t| |        /   \\   |  \\  / | |__   | |  | \\ \\  / /| |__  | |__) |" << endl;
    cout << "\t\t\t| |    _  / /\\ \\  | | \\/| |  __|  | |  |  \\ \\/ / |  __| |  _  / " << endl;
    cout << "\t\t\t| |____||/ /__   \\ | |    | | |____ | |__| | \\   /  | |____| | \\ \\ " << endl;
    cout << "\t\t\t \\______ /    \\_\\ _|    |_|______| \\___/   \\_/   |______|_|  \\_\\" << endl;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\tYOU LOST :((\n\n\n\n\n";
    std::cout << "\t\t\t\t\t your total score was: " << Score << endl;
    cout << "\t\t\t  _____              __   __  ______   ____ __       _ _____  _____  " << endl;
    cout << "\t\t\t / ____|    / \\    | \\/    |  ____| / __ \\ \\    / /  ____|  __ \\ " << endl;
    cout << "\t\t\t| |        /   \\   |  \\  / | |__   | |  | \\ \\  / /| |__  | |__) |" << endl;
    cout << "\t\t\t| |    _  / /\\ \\  | | \\/| |  __|  | |  |  \\ \\/ / |  __| |  _  / " << endl;
    cout << "\t\t\t| |____||/ /____ \\ | |    | | |____ | |__| | \\   /  | |____| | \\ \\ " << endl;
    cout << "\t\t\t \\______ /    \\_\\ _|    |_|______| \\___/   \\_/   |______|_|  \\_\\" << endl;
}

int main()
{
    srand(time(nullptr)); // initialize random seed with current time

    // Initialize the matrix
    const int SIZE = 20;
    char** matrix = new char* [20];

    for (int i = 0; i < SIZE; ++i) {
        matrix[i] = new char[20];

    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            matrix[i][j] = 'C';
        }
    }

    // Add the crystal to a random location in the matrix
    int crystal_x = rand() % SIZE;
    int crystal_y = rand() % SIZE;
    matrix[crystal_x][crystal_y] = '*';

    // Add 25 rewards to random locations in the matrix
    char rewards[] = { 'J', 'P', 'W' };
    for (int i = 0; i < 25; ++i) {
        int reward_x = rand() % SIZE;
        int reward_y = rand() % SIZE;
        while (matrix[reward_x][reward_y] != 'C') {
            reward_x = rand() % SIZE;
            reward_y = rand() % SIZE;
        }
        matrix[reward_x][reward_y] = rewards[rand() % 3];
    }

    // Add 15 death points to random locations in the matrix
    for (int i = 0; i < 15; ++i) {
        int death_x = rand() % SIZE;
        int death_y = rand() % SIZE;
        while (matrix[death_x][death_y] != 'C') {
            death_x = rand() % SIZE;
            death_y = rand() % SIZE;
        }
        matrix[death_x][death_y] = '%';
    }

    // Add 50 obstacles to random locations in the matrix
    for (int i = 0; i < 50; ++i) {
        int obstacle_x = rand() % SIZE;
        int obstacle_y = rand() % SIZE;
        while (matrix[obstacle_x][obstacle_y] != 'C') {
            obstacle_x = rand() % SIZE;
            obstacle_y = rand() % SIZE;
        }
        matrix[obstacle_x][obstacle_y] = '#';
    }

    // Add 20 monsters to random locations in the matrix
    char monsters[] = { '&', '$', '@' };
    for (int i = 0; i < 20; ++i) {
        int monster_x = rand() % SIZE;
        int monster_y = rand() % SIZE;
        while (matrix[monster_x][monster_y] != 'C') {
            monster_x = rand() % SIZE;
            monster_y = rand() % SIZE;
        }
        matrix[monster_x][monster_y] = monsters[rand() % 3];
    }

    printMatrix(matrix);

    int** adjMatrix = createAdjMatrix(matrix, ROWS);
    printAdjMatrix(adjMatrix, N);
    //findShortestPath(matrix, N);

    Node* node = NULL;
    AVLTree avl = NULL;

    // Initialize the player's position
    int player_x = 0;
    int player_y = 0;
    matrix[player_x][player_y] = '-';

    // Allow the player to move around using arrow keys
    while (true) {
        char move;
        cin >> move;
        int new_x = player_x;
        int new_y = player_y;

        if (move == 'w') {
            new_x--;
            ScoreUpdate(matrix[new_x][new_y]);
            avl.insert(node, Score);

        }
        else if (move == 'a') {
            new_y--;
            ScoreUpdate(matrix[new_x][new_y]);
            avl.insert(node, Score);

        }
        else if (move == 's') {
            new_x++;
            ScoreUpdate(matrix[new_x][new_y]);
            avl.insert(node, Score);
        }
        else if (move == 'd') {
            new_y++;
            ScoreUpdate(matrix[new_x][new_y]);
            avl.insert(node, Score);

        }
        else {
            cout << "Incorrect button pressed.\n";
            break;
        }
        // Check if the new position is valid
        if (new_x >= 0 && new_x < ROWS && new_y >= 0 && new_y < COLS && matrix[new_x][new_y] != '#') {
            // Check if the player has reached the crystal or died
            if (matrix[new_x][new_y] == '*') {
                printWonAnimation();
                break;
            }
            else if (matrix[new_x][new_y] == '%') {
                printLoseAnimation();
                return 0;
            }

            // Update the matrix with the new position of the player
            matrix[player_x][player_y] = '-';
            player_x = new_x;
            player_y = new_y;
            matrix[player_x][player_y] = '-';

            // Print the updated matrix
            printMatrix(matrix);
        }
        else {
            cout << "Invalid move, please try again!" << endl;
        }
        findShortestPath(matrix, N);
        avl.displayInventory();
    }
    
    return 0;
}
