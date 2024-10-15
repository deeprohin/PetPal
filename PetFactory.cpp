#include "PetFactory.h"

// Function to create the appropriate pet based on user input
std::unique_ptr<Pet> createPet(const std::string& user_pet) {
    if (user_pet == "adult_avo") {
        return std::make_unique<AdultAvo>();
    } else if (user_pet == "baby_avo") {
        return std::make_unique<BabyAvo>();
    } else if (user_pet == "adult_ghost") {
        return std::make_unique<AdultGhost>();
    } else if (user_pet == "baby_ghost") {
        return std::make_unique<BabyGhost>();
    }
    return nullptr; // Handle unknown pet type
}
