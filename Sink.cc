/*** sink.cc ***/
#include <string.h>
#include <omnetpp.h>
using namespace omnetpp;
class Sink : public cSimpleModule{
private :
    cStdDev delayStats;
    cOutVector delayVector;
public :
    Sink(); // constructeur
protected :
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Sink);
Sink::Sink(){

}

void Sink::initialize(){
    delayStats.setName("TotalDelay");
    delayVector.setName("Delay");
}

void Sink::finish(){
    recordScalar("Ave delay",delayStats.getMean());
    recordScalar("Number of packets",delayStats.getCount());
}

void Sink::handleMessage(cMessage *msg){
    // calculer le délai de mise en file d'attente
    simtime_t delay=simTime() - msg->getCreationTime();

    delayStats.collect(delay);
    delayVector.record(delay);

    //sumprimer le message
    delete(msg);

}
