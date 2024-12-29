#pragma once
#include <vector>
#include <string>

struct Attributes {
    std::vector<std::string> levels = {"None", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    std::vector<std::string> schools = {"None", "Abjuration", "Conjuration", "Divination", "Enchantment", "Evocation", "Illusion", "Necromancy", "Transmutation"};
    std::vector<std::string> durations = {"Instantaneous", "1 hour", "1 minute", "1 round", "10 days", "10 minutes", "24 hours", "30 days", "7 days", "6 hours", "8 hours", "Special", "Until dispelled"};
    std::vector<std::string> ranges = {"None", "1 mile", "10 feet", "100 feet", "120 feet", "150 feet", "30 feet", "300 feet", "5 feet", "500 feet", "500 miles", "60 feet", "90 feet", "Self", "Sight", "Special", "Touch", "Unlimited"};
    std::vector<std::string> area_types = {"None", "cone (15)", "cone (30)", "cone (40)", "cone (60)", "cube (10)", "cube (15)", "cube (20)", "cube (30)", "cube (5)", "cylinder (10)", "cylinder (20)", "cylinder (30)", "cylinder (40)", "line (15)", "line (30)", "sphere (10)", "sphere (15)", "sphere (20)", "sphere (30)"};
    std::vector<std::string> damage_types = {"None", "Acid", "Bludgeoning", "Cold", "Fire", "Force", "Lightning", "Necrotic", "Piercing", "Poison", "Psychic", "Radiant", "Slashing", "Thunder", "Multiple"};
    std::vector<std::string> conditions = {"None", "Blinded", "Charmed", "Deafened", "Exhaustion", "Frightened", "Grappled", "Incapacitated", "Invisible", "Paralyzed", "Petrified", "Poisoned", "Prone", "Restrained", "Stunned", "Unconscious", "Multiple"};
};
