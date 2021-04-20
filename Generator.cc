/*** Generator.cc ***/

#include <string.h>
#include <omnetpp.h>
using namespace omnetpp;
class Generator : public cSimpleModule {
    private:
        cMessage *sendMsgEvent;
    public:
        Generator (); //constructeur
    protected:
        virtual void initialize();
        virtual void finish();
        virtual void handleMessage(cMessage *msg);

};

Define_Module(Generator);
Generator::Generator(){
    sendMsgEvent = NULL;
}



void Generator::initialize(){
    //creation des paquets d'envoi
    sendMsgEvent = new cMessage("sendEvent");
    //planifier le premier événement à un moment aléatoire
    scheduleAt(par("interArrivalTime"),sendMsgEvent);

}

void Generator::finish(){

}

void Generator::handleMessage(cMessage *msg){
    cMessage * pkt;
    simtime_t departure_time;
    // creation d'un nouveau paquet;
    pkt = new cMessage("paquet");
    //envoi a la sortie
    send(pkt,"out");
    //calculer le nouveau temps de départ
    departure_time=simTime()+par("interArrivalTime");
    //programmer la génération de nouveaux paquets
    scheduleAt(departure_time, sendMsgEvent);
}
