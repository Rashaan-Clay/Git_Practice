#include <stdio.h>

struct ingredient
{
    char* name;
    int quantity;
    char* measure_type; // megatons
};

struct recipe
{
    char* name;
    char* ingredients[100];
};


int main()
{
    struct ingredient my_ingredients = {
        .name = "bomb",
        .quantity = 5,
        .measure_type = "megatons"
    };

    struct recipe my_recipe = {
        .name = "Last Meal",
        .ingredients = {my_ingredients.name, my_ingredients.quantity, my_ingredients.measure_type}
    };

    printf("%s", my_recipe.ingredients);

    return 0;
}