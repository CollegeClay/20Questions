/*
	animal.cpp

	author: L. Henke and C. Painter-Wakefield
	date: 04 November 2019

	Animal/20 questions program for CSCI 262, starter code.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>


using namespace std;

class node {
public:
    string data;
    node* left;
    node* right;
};

void play_game(node*, vector<string>&);
node* read_game_tree();
void write_game_tree(node*);
void write_preorder(ofstream&, node*);

void delete_game_tree(node*);

// TODO: Add helper method templates here, such as read_preorder().
node* read_game_tree();
node* read_preorder(ifstream& fin);
bool get_yesno(string msg);


/**
 * Handles showing the main menu/basic UI
 */
int main() {


    node* root = read_game_tree();
    if (root == NULL) return -1;


    node* currentRoot = root;

    while (true) {
        string tmp;
        int choice;

        vector<string> lines;

        cout << "Welcome to 20 questions!" << endl;
        cout << "  1) Play the game" << endl;
        cout << "  2) Save the game file" << endl;
        cout << "  3) Quit" << endl;
        cout << "Please make your selection: ";
        getline(cin, tmp);
        choice = atoi(tmp.c_str());

        switch (choice) {
            case 1:
                play_game(root, lines);
                break;
            case 2:
                cout << "Game file saved in 'animal.txt'" << endl;
                write_game_tree(root);
                break;
            case 3:
                break;
            default:
                cout << "Sorry, I don't understand." << endl << endl;
        }
        if (choice == 3) break;
    }

    delete_game_tree(root);
    return 0;
}

string trim(string s) {
    int a, b;

    for (a = 0; a < s.size() && isspace(s[a]); a++);
    for (b = s.size() - 1; b >= a && isspace(s[b]); b--);

    return s.substr(a, b - a + 1);
}


/**
 * Sets up the recursive call to the read_preorder
 * @return root of the tree
 */
node* read_game_tree() {
    // TODO: Implement me. See implementation hints! Reading is more complex than it may seem.

    string input_filename = "animal.txt";

    //cout << "What is the file you wish to read?" << endl;
    //cin >> input_filename;

    ifstream fin(input_filename);
    if (!fin) {
        cout << "Error opening \"" << input_filename << "\" for reading." << endl;
        return NULL;
    }

    return read_preorder(fin);

}

node* read_preorder(ifstream& fin){
    string line;
    string lowerNodes;


    getline(fin, line);


    node* branch = new node();

    branch->data = line;

    if(line[1] == 'Q'){
        branch->left = read_preorder(fin);
        branch->right = read_preorder(fin);
    }else{
        branch->left = nullptr;
        branch->right = nullptr;
    }

    branch->data = line.substr(2);


    return branch;
}
//NOtes 1 get rid of Q and A
//dont save until they hit the option in the menu




/**
 * Plays the game
 * @param root Root of the game tree
 */
void play_game(node* root, vector<string> &lines) {
    // TODO: Implement me.
    string userInput;
    if(get_yesno(root->data + " (y/n)")){
        if(root->left == nullptr){
            cout << "YAY! I guessed your animal!" << endl;
            lines.push_back(root->data + " y");
        }else{
            lines.push_back(root->data + " y");
            play_game(root->left, lines);
        }
        return;
    }
    lines.push_back(root->data + " n");

    if(root->right == nullptr){
        cout << "BOO! I don't know!" << endl;

        if(get_yesno("Would you like the expand the game tree? [y/n]")){
            cout << "I asked the following:" << endl;
            cout << lines.size() << endl;
            for(string s : lines){
                cout << s << endl;
            }


            node* oldAnswer = new node();
            node* newAnswer = new node();
            string temp;
            cout << "Enter a new animal in the form of a question: " << endl;
            getline(cin, newAnswer->data);
            newAnswer->left = nullptr;
            newAnswer->right = nullptr;

            oldAnswer->data = root->data;
            oldAnswer->left = nullptr;
            oldAnswer->right = nullptr;

            cout << "Now enter a question for which the answer is 'yes' for your new" << endl;
            cout << "animal, and which does not contradict your previous answers:" << endl;
            getline(cin, root->data);
            root->left = newAnswer;
            root->right = oldAnswer;
        }


    }else{
        play_game(root->right, lines);
    }


}

/**
 * Writes the game tree, sets up a recursive call to write_preorder();
 * @param root The root of the tree
 */
void write_game_tree(node* root) {
    // TODO: Implement me.



    ofstream fin("animal.txt");
    if (!fin) {
        cout << "Error opening \"" << "animal.txt" << "\" for reading." << endl;
        return;
    }
    write_preorder(fin, root);

    fin.close();
}

void write_preorder(ofstream& fin, node* root){
    if(root == nullptr){
        return;
    }
    write_preorder(fin, root->left);
    if(root->left == nullptr){
        fin << "#A " + root->data << endl;
    }else{
        fin << "#Q " + root->data << endl;
    }

    write_preorder(fin, root->right);
}




/**
 * Deletes the game tree
 * @param root Root of the game tree
 */
void delete_game_tree(node* root) {
    // Optional. Do a post-order deletion of the game tree.
    // This isn't strictly needed as the program exits after this is called,
    // which frees up all the memory anyway.
}


bool get_yesno(string msg)
{
    while (true)
    {
        string input;

        cout << msg << endl;
        getline(cin, input);

        input = trim(input);
        for (int i = 0; i < input.size(); i++)
        {
            input[i] = tolower(input[i]);
        }

        if (input == "y" || input == "yes") return true;
        if (input == "n" || input == "no") return false;

        cout << "I didn't understand that. ";
        cout << "Please enter y(es) or n(o).";
        cout << endl;
    }


}