#include <iostream>
#include <stdexcept>
#include <string>
class CoffeeMachine{
    private:
    int water;
    int beans;
    public:
    CoffeeMachine(int water,int beans):water(water),beans(beans){}
    void addWater(int number);
    void addBeans(int number);
    void makeCoffee(std::string cofe);
};
class ProblemIngredients: public std::exception{
    public:
    std::string messeg;
    ProblemIngredients(int water, int beans,int w1,int b1){
        messeg="\nНедостатньо інгредієнтів: \nвода: "+ std::to_string(water)+"    Потрібно: "+ std::to_string(w1)+"\nкавові боби: "+ std::to_string(beans)+"    Потрібно: "+ std::to_string(b1); 
    }
    const char* what() const noexcept override{
        return messeg.c_str();
    }
};
class InputIssue:public std::exception{
    public:
    std::string messeg;
    InputIssue(){
        messeg="\nПомилка вводу, спробуйте ще раз\n";
    }
    const char* what() const noexcept override{
        return messeg.c_str();
    }
};
class eraddIngresients:public std::exception{
    public:
    std::string messeg;
    eraddIngresients(){
        messeg="\nВи не можете додити від'ємну кількість або перевищувати об'єм\n";
    }
    const char* what() const noexcept override{
        return messeg.c_str();
    }
};
void CoffeeMachine::addWater(int number){
    if(number>0&&(this->water+number)<1001){
        this->water+=number;
    }else{
        throw eraddIngresients();
    }
}
void CoffeeMachine::addBeans(int number){
    if(number>0&&(this->beans+number)<101){
        this->beans+=number;
    }else{
        throw eraddIngresients();
    }
}
void CoffeeMachine::makeCoffee(std::string cofe){
    if(cofe=="Espresso"){
        if(this->water>=30&&this->beans>=10){
            this->water-=30;
            this->beans-=10;
            std::cout<<"\nЕспрессо уже готове"<<std::endl;
        }else{
            throw ProblemIngredients(this->water,this->beans,30,10);
        }
    }else if(cofe=="Americano"){
        if(this->water>=120&&this->beans>=15){
            this->water-=120;
            this->beans-=15;
            std::cout<<"\nАмерикано уже готове"<<std::endl;
        }else{
            throw ProblemIngredients(this->water,this->beans,120,15);
        }
    }else{
        throw InputIssue();
    }
}

int main () {
    CoffeeMachine cofe(0,0);
    std::string action;
    int water;
    int beans;
    std::string c;
    while(true){
        std::cout<<"\n\nВиберіть дію(refuel,coffe,end): ";
        std::cin>>action;
        if(action=="refuel"){
            try{
                std::cout<<"\nСкільки ви додасте води.max1000: ";
                std::cin>>water;
                std::cout<<"\nСкільки ви додасте кавових зерен.max100: ";
                std::cin>>beans;
                cofe.addWater(water);
                cofe.addBeans(beans);
                std::cout<<"\nВи заправили кавову машинку"<<std::endl;
            }
            catch(const eraddIngresients& e){
                std::cout<<e.what();
            }
            catch(const eraddIngresients& e){
                std::cout<<e.what();
            }
        }else if(action=="coffe"){
            try{
                std::cout<<"\nЯку каву робимо"<<std::endl;
                std::cin>>c;
                cofe.makeCoffee(c);
                
            }
            catch(const ProblemIngredients& e){
                std::cout<<e.what();
            }
            catch(const InputIssue& e){
                std::cout<<e.what();
            }
        }else if(action=="end"){
            break;
        }else{
            std::cout<<"\nВведіть дію ще раз"<<std::endl;
        }
    }
}