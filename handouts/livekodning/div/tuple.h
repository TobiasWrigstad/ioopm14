struct tuple;

struct tuple *mkTuple();

void destroyTuple(struct tuple *t);

int getFirst(struct tuple *t);

int getSecond(struct tuple *t);

void setFirst(struct tuple *t, int n);

void setSecond(struct tuple *t, int n);