
    
while (true){
    std::ofstream statsFile("pet_stats.txt");
    statsFile << user_pet<<" "<<petStats.getHealthLevel() << " "<< petStats.getSleepLevel() << " "<< petStats.getHungerLevel() << " "<< petStats.getIQLevel() << " "<< petStats.getTotalMoney() <<"\n"<<std::endl;
    // Iterate through the basket and write item details to the file
    for (const Item& item : basket) {
        outFile << item.getName() << ","   // Write the name
                << item.getStock() << "\n"; // Write the stock
    }
    statsFile.flush();
}