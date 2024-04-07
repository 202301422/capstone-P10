#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;

class Category {
public:
    string name;
    vector<Recipe*> recipes;

    Category(string n) : name(n) {}
};

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
