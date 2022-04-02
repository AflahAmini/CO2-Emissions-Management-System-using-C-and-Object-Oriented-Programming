#include <iostream>
#include <iostream>
#include <iomanip>
///***********************************************************************
//Matr.-Nr:                     3124035
//Nachname/Surname:             Amini Amir
//Vorname/Given name:           Muhammad Aflah Bin
//Uni-Email:                    muhammad.amir@stud.uni-due.de
//Studiengang/Course of studis: Computer Engineering ISE Software Engineering
//***********************************************************************/

using namespace std;
enum Frequency {
    once ,
    daily ,
    monthly ,
    weekly
};

ostream& operator<<(ostream& COUT, Frequency& a){

    switch(a){
    case once:
        return COUT;
    case daily:
        COUT << " daily ";
        return COUT;

    case monthly:
        COUT << " monthly ";
        return COUT;

    case weekly:
        COUT << " weekly ";
        return COUT;

    default:
        return COUT;
    }
}

istream& operator>>(istream& CIN, Frequency& a){
    char b ;
    while( b != 'o' && b != 'd' && b != 'm' && b != 'w' ){
        cout << "frequency input:"<< endl;
        cout << "(o) once" << endl;
        cout << "(d) daily" << endl;
        cout << "(m) monthly" << endl;
        cout << "(w) weekly" << endl;
        cout << "your choice: " ;
        CIN >> b;
        cout << "" << endl;
        switch(b){
            case 'o':
                a = once;
                return CIN;
            case 'd':
                a = daily;
                return CIN;

            case 'm':
                a = monthly;
                return CIN;
            case 'w':
                a = weekly;
                return CIN;

            default:
                cout << "Wrong input!" << endl;
        }
    }


}

class CO2Emission{
public:
    CO2Emission(){
        next = nullptr;

    }
    virtual ~CO2Emission(){

        cout << "destructor CO2Emission: done" <<endl;
        cout << "" << endl;

    }

    CO2Emission* get_next(){
        return next;
    }

    void set_next(CO2Emission* a){
         next = a;
    }

    virtual float get_co2()=0;

    virtual void print()=0;



private:
    CO2Emission *next;


};

class Transport : public CO2Emission{
public:
    Transport(){
        float distance;
        Frequency c;
        cout << "distance transport kilometers: " << endl;
        cin >> distance;
        set_km(distance);

        //todo input for frequency
        cin >> c;


    }

    Transport(float a,Frequency c = once){
        //todo parameter, default parameter
        set_km(a);
        setfrequency(c);
    }

    //destructor
    virtual ~Transport(){
        cout << "destructor Transport: " << frequency << " " << get_km() << " km done" << endl;
    }

    float get_co2(){
        //to-do
        switch(get_frequency()){
            case 0:
                return get_co2_pkm() * get_km() * 1 ;

            case 1:
                return get_co2_pkm() * get_km() * 365 ;

            case 2:
                return get_co2_pkm() * get_km() * 12 ;

            case 3:
                return get_co2_pkm() * get_km() * 52 ;

            default:
                return get_co2_pkm() * get_km() * 0 ;
        }
    }

    void print(){
        //to-do
    cout<< "transport " ;
    cout<< frequency << setprecision(1) << fixed << " " << get_km() << "km (" << setprecision(3) << fixed << get_co2_pkm() << " kg CO2/pkm) " << setprecision(1) << fixed << get_co2() << "kg CO2"<< endl;
    }

    float get_km(){
        return km;
    }
    void set_km(float a){
        km = a;
    }

    Frequency get_frequency(){
        return frequency;
    }
    void setfrequency(Frequency f){
        frequency = f;
    }

private:
    float km;
    Frequency frequency;

    virtual float get_co2_pkm() = 0;

};

class Bus: public Transport{
public:
    Bus() : Transport(){
        int a;
        float b;

        //TODO
        cout << "bus travel data input: "<< endl;

        cout << "(1) local transport"<< endl;
        cout << "(2) long distance" << endl;
        cout << "your choice: ";
        cin  >> a ;
        if(a > 1)
            setlocal_transport(0);
        else
            setlocal_transport(1);


    }

    Bus(bool typeBus, float distance): Transport(distance){
        setlocal_transport(typeBus);

    }

    //destructor
    virtual ~Bus(){
        cout << "destructor Bus: ";
        print();
    }

    void print(){
        cout<< "bus travel ";
        if(getlocal_transport() == 1){
//            cout << " local transport: " << setprecision(1) << fixed << get_km()
//            << "km (" << setprecision(3) << fixed << get_co2_pkm() << " kg CO2/pkm) "<< setprecision(1) << fixed << get_co2()  << "kg CO2"<< endl;
        cout << " local transport: "  ;
        Transport :: print();
        }
        else{
//            cout << "long distance: " << setprecision(1) << fixed << get_km()
//            << "km (" << setprecision(3) << fixed << get_co2_pkm() << " kg CO2/pkm) "<< setprecision(1) << fixed << get_co2()  << "kg CO2"<< endl;
        cout << "long distance: " ;
        Transport :: print();
        }

    }

    bool getlocal_transport(){
        return local_transport;
    }
    void setlocal_transport(bool a){
        local_transport = a;
    }

private:
    bool local_transport;
//    float km;

    float get_co2_pkm(){
        if(getlocal_transport() == 1)
            return  0.111;
        else
            return  0.036;
        }



};

class Car: public Transport{
public:
    Car() : Transport(){
        float a;
        float b;

        //TODO
        cout << "passenger car travel data input: "<< endl;

        cout << "consumption liter petrol per 100 kilometers: "<< endl;
        cin >> a;
        setl_fuel_km(a);

    }

    Car(float fuelkm, float distance): Transport(distance){
        setl_fuel_km(fuelkm);
    }

    void print(){
        cout<< "passenger car travel: " ;
        Transport :: print();

    }

    virtual ~Car(){
        cout<< "destructor Car: " ;
        print();

    }

    float getl_fuel_km(){
        return l_fuel_km;
    }
    void setl_fuel_km(float a){
        l_fuel_km = a;
    }

private:
    float l_fuel_km;

    float get_co2_pkm(){
        return 2.3 * getl_fuel_km()/ 100;
    }

};

class Cruise: public CO2Emission{
public:
    Cruise() : CO2Emission(){
        float a;
        float b;
        //TO-DO
        cout << "cruise holiday data input: "<< endl;

        cout << "number of days of the whole cruise: "<< endl;
        cin >> a;
        set_days(a);

        cout << "number of sea days: "<< endl;
        cin >> b;
        set_sea_days(b);
    }

    Cruise(float days, float sea_days) : CO2Emission(){
        set_days(days);
        set_sea_days(sea_days);
    }

    virtual ~Cruise(){
        cout<< "destructor Cruise: ";
        print();
    }

    void print(){
        cout<< "cruise holiday (without flights ): " << setprecision(0) << fixed << get_days() << "days duration with " << get_sea_days()
        << " sea days ( sea day "<< setprecision(3) << fixed << get_co2_day(1) << " kg CO2/pkm), harbour day "<< setprecision(3)
        << fixed << get_co2_day(0) << " kg CO2/pkm) " << setprecision(1) << fixed << get_co2() << " kg CO2) "<< endl;

    }


    float get_co2(){
        return get_sea_days() * get_co2_day(1) + (get_days() - get_sea_days()) * get_co2_day(0);
    }
    float get_days(){
        return days;
    }
    void set_days(float a){
        days = a;
    }
    float get_sea_days(){
        return sea_days;
    }
    void set_sea_days(float a){
        sea_days = a;
    }

private:
    float days;
    float sea_days;

    float get_co2_day(bool a){

        if( a == 1 )
            return 280;
        else
            return 190;

    }

};

class Flight: public Transport{
public:
    Flight() : Transport(){

    }

    Flight(float b) : Transport(b){


    }


    virtual ~Flight(){
        cout<< "destructor Flight : done" <<  endl;

    }

    void print(){
        cout<< "flight travel: ";
        Transport :: print();
    }


private:
    float get_co2_pkm(){
        return 0.270;
    }

};

class Train: public Transport{
public:
    Train() : Transport(){
        int local;
        int way;
        float distance;

        //to-do;
        cout << "train travel data input: "<< endl;

        cout << "(1) local transport"<< endl;
        cout << "(2) long distance" << endl;
        cout << "your choice: ";
        cin  >> local ;

        if(local > 1)
            set_local_transport(0);
        else
            set_local_transport(1);

        cout << "(1) one-way"<< endl;
        cout << "(2) return" << endl;
        cout << "your choice: ";

        cin  >> way ;

        if(way > 1)
            set_one_way(0);
        else
            set_one_way(1);
    }

    Train(bool local, float distance,bool one_way = true) : Transport (distance){

        set_one_way(one_way);
        set_local_transport(local);

    }

    virtual~Train(){
        cout<< "destructor Train : done" << endl;
    }

    float get_co2(){
        if(get_one_way() == 1)
            return get_co2_pkm() * Transport :: get_km();
        else
            return 2 * get_co2_pkm() * Transport :: get_km();

    }

    void print(){
        cout<< "train travel ";
        if(get_local_transport() == 1){
            cout << " local transport: " ;
            Transport :: print();
        }
        else{
            cout << "long distance: " ;
            Transport :: print();
        }

    }

    bool get_local_transport(){
        return local_transport;
    }
    void set_local_transport(bool a){
        local_transport = a;
    }
    bool get_one_way(){
        return one_way;
    }
    void set_one_way(bool a){
        one_way = a;
    }



private:
    bool local_transport;
    bool one_way;

    float get_co2_pkm(){
        if(get_local_transport() == 1)
            return 0.085;
        else
            return 0.035;
    }
};

class CO2Footprint {
public:
    CO2Footprint(){
        string a;
        cout << "CO2 footprint for?" << endl;
        cin >> a;
        set_name(a);
        set_emission(nullptr);
    }

    ~CO2Footprint(){
        cout<<"destructor for CO2Footprint for " << get_name() << " started..." << endl;
        // delete memeory heap
        deletelist();
        cout<< "destructor CO2Footprint done" << endl;
    }

    void print(){
        cout << "CO2 FOODPRINT FOR: " << get_name() << endl;
        CO2Emission* temp = get_emission();
//        temp->print();
//        temp = temp->get_next();
        while(temp != nullptr){
            temp->print();
            temp = temp->get_next();
        }
        cout << "TOTAL CO2 EMISSIONS: "<< setprecision(1) << fixed << get_sum_co2()<< " = " << get_sum_co2()/1000 << "tons" << endl;
    }

    string get_name(){
        return name;
    }

    void set_name(string a){
        name = a;
    }

    CO2Emission* get_emission(){
        return emission;
    }

    void set_emission(CO2Emission* a){
        emission = a;
    }

    void add(CO2Emission* a){
       if(get_emission() == nullptr){
            set_emission(a);
       }
       else{
            CO2Emission* last = get_emission();
            //traverse through list until end
            while(last->get_next() != nullptr)
            {
                last = last->get_next();
            }
            //set the next to be the object of a
            last->set_next(a);




       }
    }

    float get_sum_co2(){
        CO2Emission* temp = get_emission();
        float result;
        while(temp != nullptr){
            result += temp->get_co2();
            temp = temp->get_next();
        }
        return result;
    }

    void deletelist(){
        if(get_emission() != NULL){

            //check if emission is not null then get the next
            //pointer in list
            CO2Emission *temp, *current;
            current = get_emission();

            //get next node into temp, then delete current node, then move to next node using
            // temp, until reach head
            while(current->get_next() != nullptr) {
                temp = current->get_next();
                delete(current);
                current = temp;
            }

        }
    }

private:
    string name;
    CO2Emission*  emission;





};

class Power : public CO2Emission{
public:
    Power(){
        float a;
        cout << "power data input klo Watt hours: " << endl;
        cin >> a;
        set_kWh(a);


    }

    Power(float a){
        set_kWh(a);

    }

    void print(){
        cout<< " power " << setprecision(1) << fixed
        << get_kWh() << "kwH (" << setprecision(3) << fixed << get_co2_kWh()
        << " kg CO2/kWh) " << setprecision(1) << fixed << get_co2() << "kg CO2"<< endl;

    }
    virtual ~Power(){
        cout << "destructor Power: " << get_kWh() << " kWh done" << endl;

    }
    float get_co2(){
        return get_kWh() * get_co2_kWh();

    }

    float get_kWh(){
        return kWh;
    }
    void set_kWh(float a){
        kWh = a;
    }

private:
    float kWh;

    virtual float get_co2_kWh(){}
};

class Solar : public Power{
public:

    Solar() : Power(){

    }

    Solar(float val) : Power(val){
    }

    virtual ~Solar(){
        cout << "destructor Gas: ";
        print();
    }
    float get_co2(){
        return get_kWh() * get_co2_kWh();
    }

    void print(){

        cout << "solar " ;
        Power :: print();
    }


private:

    float get_co2_kWh(){
        return 0.143;
    }

};

class Gas : public Power{
public:
    Gas() : Power(){
        char bio ;

        cout << "gas power data input: " << endl;

        while( bio != 'b' && bio != 'f'){
            cout << "type of gas: "<< endl;;
            cout << "(b) bio gas "<< endl;
            cout << "(f)fossil natural gas "<< endl;
            cin  >> bio ;
            switch(bio){
                case 'b' :
                    set_bio(1);
                    break;

                case 'f' :
                    set_bio(0);
                    break;

                default:
                    cout << "Please enter correct input!" << endl;

            }
        }
    }

    Gas(float kWh, bool bio = false) : Power(kWh){
        set_bio(bio);

    }

    float get_co2(){
        return get_kWh() * get_co2_kWh();
    }

    void print(){
        if(get_bio()){
            cout << "bio gas";
            Power :: print();
        }
        else{
            cout << "fossil natural gas";
            Power :: print();
        }
    }

    bool get_bio(){
        return bio;
    }
    void set_bio(bool a){
        bio = a;
    }

private:

    bool bio;

    float get_co2_kWh(){
        if(get_bio())
            return 0.230;
        else
            return 0.819;
    }

};




int main()
{
    Bus *b2 = new Bus(true, 2200);

    Car *c2 = new Car(7.5, 5500);

    Cruise *h2 = new Cruise(14, 3);

    Flight *f2 = new Flight(2669.9);

    Train *t2 = new Train(false, 628.8, false);

    //Part 2 task
    Solar *s2 = new Solar(1500);
    Gas *g2 = new Gas(1500);

    CO2Footprint f = CO2Footprint();

    f.add(b2);
    f.add(c2);
    f.add(h2);
    f.add(f2);
    f.add(t2);

    //Task 2
    f.add(s2);
    f.add(g2);



    char s = '1';
    while(s!='e'){
        cout<< "(e) end"<< endl;
        cout<< "(b) bus transport" << endl;
        cout<< "(c) car transport" << endl;
        cout<< "(f) flight tranport"<<endl;
        cout<< "(h) holiday cruise"<<endl;
        cout<< "(t) train transport"<<endl;
        cout<< "(s) power from solar"<< endl;
        cout<< "(g) power from gas"<< endl;
        cout<< "(p) print all"<<endl;


        cin >> s;

        switch(s){
            case 'e' :
                break;
            case 'b' :{
                Bus *b = new Bus();
                f.add(b);
                break;
            }
            case 'c' :{
                Car *c = new Car();
                f.add(c);
                break;
            }
            case 'f' :{
                Flight *fl = new Flight();
                f.add(fl);
                break;
            }
            case 'h' :{
                Cruise *h = new Cruise();
                f.add(h);
                break;
            }
            case 't' :{
                Train *t = new Train();
                f.add(t);
                break;
            }
            case 's' :{
                Solar *s = new Solar();
                f.add(s);
                break;
            }
            case 'g' :{
                Gas *g = new Gas();
                f.add(g);
                break;
            }
            case 'p' :{
                f.print();
                break;
            }

            default:
                cout<< "Incorrect input!" << endl;
        }

    }


    return 0;
}
