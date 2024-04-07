#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;

class Category {
public:
    string name;
    vector<Recipe*> recipes;

    Category(string n) : name(n) {}
};
class MealPlan{
    public:
    string day;
    bool added=false;
    unordered_map<string, Recipe*> meals;
    void addmeal(string type,Recipe* r)
    {
        meals[type]=r;added=true;
    }
};
int setday(string Day){
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
    void addCategory(string categoryName) {
        if (categories.find(categoryName) == categories.end()) {
            categories[categoryName] = new Category(categoryName);
        }
    }

    void addRecipeToCategory(Recipe* recipe, string categoryName) {
        if (categories.find(categoryName) != categories.end()) {
            categories[categoryName]->recipes.push_back(recipe);
        }
    }

    vector<Recipe*> getRecipesInCategory(string categoryName) {
        if (categories.find(categoryName) != categories.end()) {
            return categories[categoryName]->recipes;
        }
        return {};
    }
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

void searchRecipesByIngredient(const vector<Recipe>& R, const string& ingredient) {
    bool found = false;
    cout << "Recipes containing " << ingredient << ":" << endl;
    for (const auto& recipe : R) {
        for (const auto& ing : recipe.ingredients) {
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
    cout<<"0: To insert recipe:\n1: To adding a catagory:\n2: To adding recipe in a category:\n3: To plan your meal\n4: To display your meal\n5: To search recipe\n6: To search recipe by ingredients\n7: To display categories\n-1: Exit\n";
    cin>>option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    MealPlan plan[7];
    RecipeManager rm;
    label:
    
    if(option==0)
    { char add;
      do
      {insertRecipe(R);
      cout<<"Do you want to add more recipe(y/n):";
      cin>>add;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      while(add=='y');
    }

    else if(option==1){
        cout<<"Enter name of a catagory you want to add: ";
        string cate;
        cin>>cate;
        rm.addCategory(cate);
    }
    
    else if(option==2){
        addtocat(R);
    }
    
    else if(option==3)
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
            cout<<"Enter the name of the reciepe to add in plan:";
            cin>>rec;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            vector<Recipe>::iterator it;
            for(it = R.begin(); it != R.end()&&it->name != rec; ++it) {
            }
            if(it == R.end())
                cout << "The recipe of " << rec << " doesn't exist." << endl;
            else {
                plan[index].addmeal(type, &(*it)); 
                cout << "The recipe of " << rec << " added successfully in your meal plan." << endl;
            }
            cout<<"\nDo you want to add more recipe in your plan(y/n):\n";
            cin>>add;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }while(add=='y');
    }

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
    
    else if(option==6)
    {
    cout << "Enter an ingredient to search for: ";
    string ingredient;
    getline(cin, ingredient);
    searchRecipesByIngredient(R, ingredient);
    }
    
    else if(option==5){
        searchRecipe(R);
    }

    else if(option==7){
        rm.displayCategories();
    }
    
    cout<<"0: To insert recipe:\n1: To adding a catagory:\n2: To adding recipe in a category:\n3: To plan your meal\n4: To display your meal\n5: To search recipe\n6: To search recipe by ingredients\n7: To display categories\n-1: Exit\n";
    cin>>option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(option!=-1)
    goto label;    
    return 0;
}
