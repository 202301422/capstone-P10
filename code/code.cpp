#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;
class Recipe {
 public:
    string name; // contains recipe's name
    vector<string> ingred; // contain's recipe's ingredients as vector of strings 
    string instructions;  // contains instructions about how to make recipe
    Recipe(string n,vector<string> ing,string instr):name(n),ingred(ing),instructions(move(instr)){}//constructer for object of recipe class
    string getingredAsString() const {//function to add ingredients in vector
        string ingredStr;
        for (const auto& ingredient : ingred) {
            ingredStr += ingredient + ", ";
        }
        if (!ingredStr.empty()) {
            ingredStr.pop_back();
            ingredStr.pop_back();
        }
        return ingredStr;
    }
    string getName() const {
        return name;
    }
    string getInstructions() const {
        return instructions;
    }
};
class Category {
public:
    string name;
    vector<Recipe*> recipes;

    Category(string n) : name(n) {}
};
class MealPlan{
    public:
    string day; // to store day for which you are planning the meal.
    bool added=false; // indicates that the meal plan is added or not
    unordered_map<string, Recipe*> meals; // map to store meal-type and recipe name
    void addmeal(string type,Recipe* r)
    {
        meals[type]=r;added=true;// makes added true whenever you enter any mealplan
    }
};
int setday(string Day){// to return index according to the day for an array.
    if(Day=="monday"||Day=="Monday")
    {
        return 0;
    }
    else if(Day=="tuesday"||Day=="Tuesday")
    {
        return 1;
    }
    if(Day=="wednesday"||Day=="Wednesday")
    {
        return 2;
    }if(Day=="Thursday"||Day=="thursday")
    {
        return 3;
    }if(Day=="Friday"||Day=="friday")
    {
        return 4;
    }if(Day=="saturday"||Day=="Saturday")
    {
        return 5;
    }if(Day=="Sunday"||Day=="sunday")
    {
        return 6;
    }
} 
class RecipeManager {
private:
    unordered_map<string, Category*> categories;

public:
//This function is for adding the category.
    void addCategory(string categoryName) {
        if (categories.find(categoryName) == categories.end()) {
            categories[categoryName] = new Category(categoryName);
        }
    }
 //This function is for adding the recipe in a specific category.
    void addRecipeToCategory(Recipe* recipe, string categoryName) {
        if (categories.find(categoryName) != categories.end()) {
            categories[categoryName]->recipes.push_back(recipe);
        }
    }
 //This vector function will take the recipe in a category.
    vector<Recipe*> getRecipesInCategory(string categoryName) {
        if (categories.find(categoryName) != categories.end()) {
            return categories[categoryName]->recipes;
        }
        return {};
    }
 //This display function will display how many categories are there.
    void displayCategories() {
        cout << "Categories:" << endl;
        for (auto const& category : categories) {
            cout << category.first << endl;
        }
    }
};
//This function will take a vector object as input and will insert a recipe as you need.
void insertRecipe(vector<Recipe>& R) {
    string recipeName, ingredient, instructions;
    vector<string> ingred;
    cout << "Enter recipe name: ";  
    getline(cin, recipeName);  //This will get name of the reciepe.

    cout << "Enter ingred (type 'done' to finish): ";
    while (getline(cin, ingredient) && ingredient != "done") {
        ingred.push_back(ingredient);   //In this loop we will take ingredients.
        cout << "Add another ingredient (or type 'done'): ";
    }

    cout << "Enter instructions: ";
    getline(cin, instructions);  //Here we will take instructions.

    R.emplace_back(recipeName, ingred, instructions);
    cout << "Recipe added successfully!" << endl;
}
//We created this function for searching a reciepe by it's name.
void searchRecipe(const vector<Recipe>& R) {
    string searchRecipe;
    cout << "Enter the name of the recipe you want instructions for: ";
    getline(cin, searchRecipe); //Here we will take name of that reciepe.

    bool found = false;  //Here it will search name of reciepe.
    for (const auto& recipe : R) {
        if (recipe.getName() == searchRecipe) {
            found = true;
            cout << "Recipe found!" << endl;
            cout << "ingred: " << recipe.getingredAsString() << endl;
            cout << "Instructions: " << recipe.getInstructions() << endl;
            break;
        }
    }
    if (!found) {
        cout << "Recipe not found!" << endl;   //And if it is not found it will print this.
    }
}

//This function is for searching recipe by any ingredient.
void searchRecipesByIngredient(const vector<Recipe>& R, const string& ingredient) {
    bool found = false;
    cout << "Recipes containing " << ingredient << ":" << endl;
    for (const auto& recipe : R) {
        for (const auto& ing : recipe.ingred) {
            if (ing == ingredient) {
                cout << "- " << recipe.getName() << endl;
                found = true;
                break; // Breaks the inner loop if ingredient is found
            }
        }
    }

    if (!found) {
        cout << "No recipes found containing " << ingredient << "." << endl;
    }
}

//This is for adding a category.
void addtocat(vector<Recipe>& R){
    insertRecipe(R);
    RecipeManager rm;
    cout<<"Enter category where you want to add this recipe: ";
    string cate;
    cin>>cate;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    rm.addRecipeToCategory(&R.back(),cate);
}
int main() {
    cout<<"WELCOME TO RECIPE MANAGER!!\n\n\n";
    int option;
    vector<Recipe> R;
    Recipe soup("soup",{"tomatoes","water"},"boil the water");
    Recipe cake("cake",{"bread","cream"},"put cream on bread");
 //Here we gave user the options for doing specific tasks, there are 7 different tasks.
    cout<<"0: To insert recipe:\n1: To adding a catagory:\n2: To adding recipe in a category:\n3: To plan your meal\n4: To display your meal\n5: To search recipe\n6: To search recipe by ingredients\n7: To display categories\n-1: Exit\n";
    cin>>option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //to absorb a new line character "\n".
    MealPlan plan[7];
    RecipeManager rm;
    label:
    
    if(option==0) //This option is for inserting a recipe.
    { char add;
      do
      {insertRecipe(R);// inserts recipe
      cout<<"Do you want to add more recipe(y/n):";
      cin>>add; // variable which will loop this until user doesn't enter n
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      while(add=='y');
    }
     
//This option is for adding a category.
    else if(option==1){
        cout<<"Enter name of a category you want to add: ";
        string cate;
        cin>>cate;
        rm.addCategory(cate);
    }
    
    else if(option==2){
        addtocat(R);
    }
    
    else if(option==3) //This option is for meal planning.
    {
        char add;
        int index;
        string DAY;
        string type; 
        do
        {   
            cout<<"Enter the day for which you want to plan:";
            cin>>DAY;
            index=setday(DAY);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            plan[index].day=DAY;
            
            cout<<"Enter the type of meal(E.G. Breakfast,Lunch,Dinner):";
            cin>>type;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            string rec;
            cout<<"Enter the name of the recipe to add in plan:";
            cin>>rec;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            vector<Recipe>::iterator it; // points to vector of recipe
            for(it = R.begin(); it != R.end()&&it->name != rec; ++it) {// if recipe found with same name then it will point to it and loop will stop
            }
            if(it == R.end())// if it doesn't find
                cout << "The recipe of " << rec << " doesn't exist." << endl;
            else {// adds recipe in object of recipe which is present in array
                plan[index].addmeal(type, &(*it)); 
                cout << "The recipe of " << rec << " added successfully in your meal plan." << endl;
            }
            cout<<"\nDo you want to add more recipe in your plan(y/n):\n";
            cin>>add;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }while(add=='y');
    }
     
//This option is for displaying whole meal plan it will show only that day which are alloted to them.
    else if(option==4)
    {cout<<"Your this week's meal plan:"<<endl;
      for (int i = 0; i < 7; i++) 
      {
            if (plan[i].added) 
            {
                cout << "\nDay: " << plan[i].day << endl;
                for (auto it = plan[i].meals.begin(); it != plan[i].meals.end(); ++it) {
                    cout << "Type: " << it->first << endl;
                    cout << "Recipe: " << it->second->name << endl;
                }
            }
      }cout<<endl;
    }
     //Option 6 is for searching a recipe by its ingredients.
    else if(option==6)
    {
    cout << "Enter an ingredient to search for: ";
    string ingredient;
    getline(cin, ingredient);
    searchRecipesByIngredient(R, ingredient);
    }
     //This is for searching a recipe.
    else if(option==5){
        searchRecipe(R);
    }
//This option is for displaying all categories.
    else if(option==7){
        rm.displayCategories();
    }
    
    cout<<"0: To insert recipe:\n1: To adding a catagory:\n2: To adding recipe in a category:\n3: To plan your meal\n4: To display your meal\n5: To search recipe\n6: To search recipe by ingredients\n7: To display categories\n-1: Exit\n";
    cin>>option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(option!=-1) //This will terminate program.
    goto label;    
    return 0;
}
