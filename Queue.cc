/*** queue.cc ***/
#include <string.h>
#include <omnetpp.h>
using namespace omnetpp;
class Queue : public cSimpleModule {
private :
    //variable local
    cQueue buffer;
    cMessage *endServiceEvent;
    simtime_t service_time;

public :
    Queue(); // constructeur


protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Queue);
Queue::Queue(){
    endServiceEvent = NULL;
}



void Queue::initialize(){
    endServiceEvent=new cMessage("endService");
}

void Queue::finish(){

}

void Queue::handleMessage(cMessage *msg){
    cMessage *pkt;
    //si msg est endServiceEvent, alors
    // defiler et envoyer le pkt à la sortie
    //si un autre pkt est disponible dans le buffer, alors
    //demarer un nouveau service
    //si msg est un paquet, alors
    //enfiler le pkt
    //si le serveur tourne au ralenti, alors
    ////demarer un nouveau service

    if (msg==endServiceEvent){
        //defiler
        pkt = (cMessage*)buffer.pop();
        //envoyer
        send(pkt,"out");
        if(!buffer.empty()) { //si un autre pkt est disponible dans le buffer
            service_time=par("serviceTime");
            scheduleAt(simTime()+service_time,endServiceEvent);
        }
    }else{//si msg est un paquet
        //enfiler
        buffer.insert(msg);
        //si le serveur tourne au ralenti
        if (!endServiceEvent->isScheduled()) {
            //demarer un nouveau service
            service_time=par("serviceTime");
            scheduleAt(simTime()+service_time,endServiceEvent);
        }
    }

}
