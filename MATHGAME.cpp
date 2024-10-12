#include "MATHGAME.h"

math_game::math_game(){
    math_audio.openFromFile("Lobby Music (Original Soundtrack).mp3");
    math_audio.setVolume(100);
    math_audio.play();
    correct_answers=0;
    number_of_answers=0;
    total_time=50.0; //initalize how much time is given to solve math questions
    std::srand(static_cast<unsigned int>(std::time(0)));
    current_input="";
    game_window = new sf::RenderWindow(sf::VideoMode(1920,1080),"Math Game");
    game_window->display();
    display_intro();
    rules_page();
    game_window->clear();
    timer.restart();
    run();
}

void math_game::generate_question(){
    //resetting user input
    current_input="";
    //generating numbers and operator
    int num1=std::rand()%100;
    int num2=std::rand()%100;
    char operation = "+-*"[std::rand() % 3];
    //calculating correct answer
    if (operation == '+') {
        current_answer = num1 + num2;
    } else if (operation == '-') {
        current_answer = num1 - num2;
    } else {
        current_answer = num1 * num2;
    }
    current_question = std::to_string(num1) + " " + operation + " " + std::to_string(num2) + " = ?";
    //std::cout << "Question: " << current_question << std::endl;
}

math_game::~math_game(){
    math_audio.pause();
    delete game_window;
}

void math_game::run(){
    for(int i=0;i<5;i++){
        generate_question();
        while (game_window->isOpen()){
            bool has_entered=false;
            while(game_window->pollEvent(ev)){
                if (ev.type == sf::Event::Closed|| ev.type==sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
                    game_window->close();
                }
                if (ev.type == sf::Event::KeyPressed){
                    if (ev.key.code == sf::Keyboard::Enter){
                        if(current_input.empty()){
                            break;
                        }
                        if(current_answer==std::stoi(current_input)){
                            correct_answers++;
                        }
                        number_of_answers++;
                        has_entered=true;
                        break;
                    }
                    if(ev.key.code == sf::Keyboard::Dash){
                        current_input = '-' + current_input; 
                    }
                    if (ev.key.code == sf::Keyboard::BackSpace) {
                        if (!current_input.empty()) {
                            current_input = current_input.substr(0, current_input.size() - 1);
                        }
                    }
                    if (ev.key.code >= sf::Keyboard::Num0 && ev.key.code <= sf::Keyboard::Num9){
                        int number_entered = ev.key.code - sf::Keyboard::Num0;
                        current_input+=std::to_string(number_entered);
                    }
                    
                }
            }
            render();
            if(has_entered){
                break;
            }
        }
    }
    std::cout << "You got " << correct_answers << " out of 5 correct!" << std::endl;
    display_results();
}

void math_game::render(){
    game_window->clear(sf::Color(230, 230, 220));
    sf::Font font;
    if (!font.loadFromFile("dogica.ttf")){  
        std::cout << "Error, font not found" << std::endl;
    }
    //displaying the math question
    sf::Text questionText;
    questionText.setFont(font);
    questionText.setString(current_question);
    questionText.setCharacterSize(55); 
    questionText.setFillColor(sf::Color::Black);
    questionText.setPosition(480,300); 
    // Draw the question text
    game_window->draw(questionText);
    
    // Displaying user input
    sf::Text input_text;
    input_text.setFont(font);
    input_text.setString(current_input);
    input_text.setCharacterSize(40);
    input_text.setFillColor(sf::Color::Black);
    input_text.setPosition(680, 400); 
    //drawing user input
    game_window->draw(input_text);

    sf::Text score_text;
    score_text.setFont(font);
    score_text.setFillColor(sf::Color::Black);
    score_text.setString("Score: "+std::to_string(correct_answers));
    score_text.setCharacterSize(40);
    score_text.setPosition(20, 20);
    game_window->draw(score_text);

    //drawing countdown timer
    sf::Text timer_text;
    timer_text.setFont(font);
    double remaining_time=51-timer.getElapsedTime().asSeconds(); //timer for how long user has left
    int remaining_time_int=remaining_time;
    timer_text.setString(std::to_string(remaining_time_int));
    timer_text.setCharacterSize(40);
    timer_text.setPosition(700, 100);
    if(remaining_time>=30){
        timer_text.setFillColor(sf::Color::Black);
    }else if(remaining_time>10){
        timer_text.setFillColor(sf::Color(255, 165, 0));
    }else{
        timer_text.setFillColor(sf::Color::Red); 
    }
    game_window->draw(timer_text);
    game_window->display();
    if(remaining_time<=0){
        display_results();
    }
}

void math_game::display_results(){
    game_window->clear(sf::Color(230, 230, 220));
    sf::Font font;
    if (!font.loadFromFile("Regular.ttf")){  
        std::cout << "Error, font not found" << std::endl;
    }

    sf::Text score_text;
    score_text.setFont(font);
    score_text.setFillColor(sf::Color::Black);
    score_text.setString("  GAME OVER!!\n\nPoints Scored: " + std::to_string(correct_answers) + "\nCoins earned: " + std::to_string(correct_answers * 10));
    score_text.setCharacterSize(70);
    score_text.setPosition(550,300);

    game_window->draw(score_text);
    game_window->display();
    while (game_window->isOpen()) {
        sf::Event event;
        while (game_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed|| event.type==sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                game_window->close(); // Close the window when the close event is triggered
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                game_window->close(); // Close the game when Enter is pressed
            }
        }
    }
}

void math_game::display_intro(){
    sf::Texture texture_1;
    texture_1.loadFromFile("New Piskel copy (1).png");//New Piskel.png
    sf::Sprite sprite;
    sprite.setTexture(texture_1);
    sprite.setPosition(280, 120);
    sprite.setScale(30.0f, 30.0f);

    Animation intro_scene(&texture_1,sf::Vector2u(6,1),0.3f); 
    float delta_time=0.0f;
    sf::Clock clock;
    sf::Clock total_time;
    while(game_window->isOpen()){
         sf::Event event;
        while (game_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed|| event.type==sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                game_window->close(); // Close the window when the close event is triggered
            }
        }
        delta_time=clock.restart().asSeconds();
        intro_scene.update(0,delta_time);
        sprite.setTextureRect(intro_scene.uv_rect);
        game_window->clear(sf::Color(196, 164, 132));
        game_window->draw(sprite);
        game_window->display();
        if(total_time.getElapsedTime().asSeconds()>=3){
            break;
        }
    }
}

void math_game::rules_page(){
    sf::Clock clock;
    sf::Font font;
    if (!font.loadFromFile("Regular.ttf")){  
        std::cout << "Error, font not found" << std::endl;
    }
    while(game_window->isOpen()){
        sf::Event event;
        bool escape=false;
        while (game_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed|| event.type==sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                game_window->close(); // Close the window when the close event is triggered
            }
            if(event.type==sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter){
                escape=true;
            }
        }
        game_window->clear(sf::Color(230, 230, 220));
        if(escape){
            break;
        }

        sf::Text welcome1;
        welcome1.setFont(font);
        welcome1.setFillColor(sf::Color::Black);
        welcome1.setString("Welcome to PetPal Math Game!\n\n\nInstructions:\n\n1) You have 50 seconds to answer 5 math questions\n\n2) Type solution and hit enter to answer\n\n3) Type - for negative\n\n4) Use delete key to remove entered number\n\n5) Press Enter to Start Game\n\n\nGood Luck!");
        welcome1.setCharacterSize(35);
        welcome1.setPosition(30, 30);
        game_window->draw(welcome1);
        game_window->display();
     }
}
