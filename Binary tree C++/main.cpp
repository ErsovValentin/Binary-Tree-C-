#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <math.h>


/* IN this project are class 'Games', struct  binaryTree_node.
Class Games use the file "50 games.txt" and takes from there information for the fields.
Struct  binaryTree_node create binary tree and composed of left leaf, right leaf and data (Object of class Games)
Binary tree has 3 types of tree's Traversal (Inorder, Postorder, Preorder)
*/

using namespace std;


/// OOP; Create class Games

class Games
    {
    public:
        ///Fields
        int id;
        string name;
        float rating;
        int year;
        string genre;
        string developer;
        string country;

    public :

        ///Default Constructor
        Games()
        {
            id = 0;
            name = "NONE";
            rating = 0.0;
            year = 2000;
            genre = "NONE";
            developer = "NONE";
            country = "NONE";
           // next = NULL;
        }

        /// set() - fields of object
        void setId(int a){id = a;}
        void setName(string a){name = a;}
        void setRating(float a){rating = a;}
        void setYear(int a){year = a;}
        void setGenre(string a){genre = a;}
        void setDeveloper(string a){developer = a;}
        void setCountry(string a){country = a;}
        void setGame()
        {
            cout<<"Enter the id of game : ";
            cin>>id;
            cout<<"Enter the name of game : ";
            getline(cin,name);
            cout<<"Enter the rating of game : ";
            cin>>rating;
            cout<<"Enter the year of game : ";
            cin>>year;
            cout<<"Enter the genre of game : ";
            getline(cin,genre);
            cout<<"Enter the developer of game : ";
            getline(cin,developer);
            cout<<"Enter the country of game : ";
            getline(cin,country);
        }

        /// get() - fields of object
        int getId(){return id;}
        string getName(){return name;}
        float getRating(){return rating;}
        int getYear(){return year;}
        string getGenre(){return genre;}
        string getDeveloper(){return developer;}
        string getCountry(){return country;}

        ///prototypes of methods
        friend ostream& operator << (ostream& out, Games& current);
        friend istream& operator >> (istream& in, Games& current);
        void show();
        void inputFromFile(ifstream& file);


        ///overloading operators  { > , < , >= , <= , == } comparison by field 'NAME'

        int operator > (Games& current)
        {
            if(name.compare(current.name)>0)
            {
                return 1;
            }
            return (0);
        }

        int operator < (Games& current)
        {
            if(name.compare(current.name)<0)
            {
                return 1;
            }
            return (0);
        }

        int operator <= (Games& current)
        {
            if(name.compare(current.name) <= 0)
            {
                return 1;
            }
            return (0);
        }

        int operator >=(Games& current)
        {
            if(name.compare(current.name) >= 0)
            {
                return 1;
            }
            return (0);
        }

        int operator ==(Games& current)
        {
            if(name.compare(current.name) == 0)
            {
                return(1);
            }
            return(0);
        }



        void operator = (Games &current)
        {
            id = current.id;
            name = current.name;
            rating = current.rating;
            year = current.year;
            genre = current.genre;
            developer = current.developer;
            country = current.country;
        }

    };

     ///overloading operator >> to getLine from file and put it into the field
    istream& operator >> (istream& file, Games& current)
        {
            string temp;
            getline(file,temp);
            current.id = atoi(temp.c_str());

            getline(file,current.name);

            getline(file,temp);
            current.rating = atof(temp.c_str());

            getline(file,temp);
            current.year = atoi(temp.c_str());

            getline(file,current.genre);

            getline(file,current.developer);

            getline(file,current.country);
        return file;
        }


    /// overloading operator << output correctly the object
    ostream& operator << (ostream& out, Games& current)
        {
            out << setiosflags(ios::left)<<setw(5)<<current.id<<setw(20)<<current.name;
            out << setw(5) << current.rating << setw(6) <<current.year <<setw(12)<<current.genre<<setw(20)<< current.developer << setw(20) << current.country;
            return out;
        }

        void Games:: show()
        {
            cout << this;
        }

        void Games:: inputFromFile(ifstream& file)
        {
            file >> *this;
        }


/// Binary Tree


 struct binaryTree_node
{
    Games data ;
    binaryTree_node *left;
    binaryTree_node *right;
};


///Create the leaf of tree
binaryTree_node *createNode(Games data)
        {
            binaryTree_node *new_node = new binaryTree_node();

            new_node->data = data;
            new_node->left = NULL;
            new_node->right = NULL;
            return new_node;
        }

/// Insert the leaf of tree
binaryTree_node *insertNode(binaryTree_node *root,Games data)
        {
            if(root == NULL)
            {
                root = createNode(data);
            }
            else if(data <= root->data )
            {
                root->left = insertNode(root->left,data);
            }
            else if(data > root->data )
            {
                root->right = insertNode(root->right,data);
            }
            return root;
        }


///Find the end of binary tree
binaryTree_node *findMinNode(binaryTree_node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

///Delete the leaf with desired Game name
binaryTree_node *delete_binaryTree(binaryTree_node *root,Games data)
{
    if(root == NULL)
    {
        return root;
    }
    else if (data < root->data)
    {
        root->left = delete_binaryTree(root->left,data);
    }
    else if (data > root->data)
    {
        root->right = delete_binaryTree(root->right,data);
    }
    else
    {
        if(root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        else if(root->left == NULL)
        {
            binaryTree_node *tmp = root;
            root = root->right;
            delete tmp;
        }
        else if(root->right == NULL)
        {
            binaryTree_node *tmp = root;
            root = root->left;
            delete tmp;
        }
        else
        {
            binaryTree_node *min = findMinNode(root->right);
            root->data = min->data;
            root->right = delete_binaryTree(root->right, min->data);
        }
    }
    return root;
 }

/// Preorder Traversal of binary tree
void preorderTraversal(binaryTree_node *leaf)
{
    if(leaf == NULL) return;
    else
    {
        preorderTraversal(leaf->left);

        cout<<leaf->data<<endl;

    }
    preorderTraversal(leaf->right);
}

/// Inorder Traversal of binary tree
void inorderTraversal (binaryTree_node *leaf)
{
    if(leaf==NULL) return;
    cout << leaf->data << endl;

    inorderTraversal(leaf->left);
    inorderTraversal(leaf->right);
}


/// Postorder Traversal of binary tree
void postorderTraversal(binaryTree_node *leaf)
{
    if(leaf)
    {
        postorderTraversal(leaf->left);
        postorderTraversal(leaf->right);
        cout<<leaf->data<<endl;
    }
}

/// Insert into binary tree all notes from File "50 games.txt"
binaryTree_node *insertDataFromFile(binaryTree_node *root)
{
    ifstream File("50 games.txt");
    Games temp;
    temp.inputFromFile(File);
    while(!File.eof())
    {
        temp.inputFromFile(File);
        root = insertNode(root,temp);
    }
    File.close();
    return root;
}

/// Delete all binary tree
void delete_All_binaryTree(binaryTree_node *root)
{
    root = delete_binaryTree(root,root->data);
}


int position_of_element;
/// Search the element in file
int searchNode(binaryTree_node *root, string data)
{
    if (root == NULL)
    {
        cout<<"Element not found"<<endl;
        return 0;
    }
    else if (data == root->data.getName())
    {
        cout<<root->data<<endl;
        return position_of_element;
    }
    else if (data <= root->data.getName())
    {
        position_of_element++;
        return searchNode(root->left, data);
    }
    else
    {
        position_of_element++;
        return searchNode(root->right, data);
    }

}

///Find desired element in binary tree
void find_desired_elem(binaryTree_node *root)
{
    string temp;
    position_of_element = 1;
    cout<< "Enter the name of desired game : ";
    getline(cin,temp);
    cout<<"Position of desired element : "<<searchNode(root,temp)<<endl;
}

/// Main
int main()
{
    binaryTree_node *root = NULL;

    root = insertDataFromFile(root);

    cout<< "Inorder Traversal of binary tree : "<<endl<<endl;
    inorderTraversal(root);

    cout<< "Preorder Traversal of binary tree : "<<endl<<endl;
    preorderTraversal(root);

    cout<< "Postorder Traversal of binary tree : "<<endl<<endl;
    postorderTraversal(root);

    find_desired_elem(root);

    delete_All_binaryTree(root);

    return 0;
}
