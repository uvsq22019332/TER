// *** mm1.ned ***

simple Generator
{
    parameters:
        volatile double interArrivalTime; //sec
        @display("i=block/source");
    gates:
        output out;
}



simple Queue
{
    parameters:
        volatile double serviceTime; //sec
        @display("i=block/queue");
    gates:
        input in;
        output out;
}


simple Sink
{
    parameters:
        @display("i=block/sink");
    gates:
        input in;
}

network MM1
{
    @display("bgb=349,113");
    submodules:
        gen: Generator {
            @display("p=28,30");
        }
        queue: Queue {
            @display("p=165,30");
        }
        sink: Sink {

            @display("p=301,30");
        }
    connections:
        gen.out --> queue.in;
        queue.out --> sink.in;
}