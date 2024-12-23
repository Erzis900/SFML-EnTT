namespace features::enemy::components
{
    struct aiControlled
    {
        bool isControlled;
        aiControlled(bool controlled) : isControlled(controlled) {}
    };
}