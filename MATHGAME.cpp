#include "MATHGAME.h"

math_game::math_game(){
    correctAnswers=0;
    number_of_answers=0;
    total_time=50.0; //initalize how much time is given to solve math questions
    std::srand(static_cast<unsigned int>(std::time(0)));
    current_input="";
    game_window = new sf::RenderWindow(sf::VideoMode(1920,1080),"Math Game");
    game_window->display();
    display_intro();
    game_window->clear();
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
    delete game_window;
}

void math_game::run(){
    for(int i=0;i<5;i++){
        generate_question();
        while (game_window->isOpen()){
            bool has_entered=false;
            while(game_window->pollEvent(ev)){
                if (ev.type == sf::Event::Closed){
                    game_window->close();
                }
                if (ev.type == sf::Event::KeyPressed){
                    if (ev.key.code == sf::Keyboard::Enter){
                        if(current_answer==std::stoi(current_input)){
                            correctAnswers++;
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
    std::cout << "You got " << correctAnswers << " out of 5 correct!" << std::endl;
}

void math_game::render(){
    game_window->clear(sf::Color(245, 245, 220));
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
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setString(current_input);
    inputText.setCharacterSize(40);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(680, 400); 
    //drawing user input
    game_window->draw(inputText);

    //drawing countdown timer
    sf::Text timerText;
    timerText.setFont(font);
    double remaining_time=54-timer.getElapsedTime().asSeconds();
    int remaining_time_int=remaining_time;
    timerText.setString(std::to_string(remaining_time_int));
    timerText.setCharacterSize(40);
    timerText.setPosition(700, 100);
    if(remaining_time>=30){
        timerText.setFillColor(sf::Color::Black);
    }else if(remaining_time>10){
        timerText.setFillColor(sf::Color(255, 165, 0));
    }else{
        timerText.setFillColor(sf::Color::Red); 
    }
    game_window->draw(timerText);
    game_window->display();
    if(number_of_answers==5||remaining_time<=0){
        display_results();
    }
}

void math_game::display_results(){
}

void math_game::display_intro(){
    sf::Texture texture_1;
    texture_1.loadFromFile("New Piskel.png");
    sf::Sprite sprite;
    sprite.setTexture(texture_1);
    sprite.setPosition(330, 20);
    sprite.setScale(25.0f, 25.0f);

    Animation intro_scene(&texture_1,sf::Vector2u(2,3),0.3f);
    float delta_time=0.0f;
    sf::Clock clock;
    sf::Clock total_time;
    while(game_window->isOpen()){
         sf::Event event;
        while (game_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
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
