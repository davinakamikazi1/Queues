# Queues
Data members:
• Five data members:
◦ The arr data member, which is a pointer to type T
◦ The total capacity of the array
◦ The number of slots currently used in the queue
◦ The head of the queue
◦ The tail of the queue
All can be initialized to nullptr or zero. Note on naming. Data member #2 shouldn’t be named size,
as the code has a method called size(). Also, data members #3 and #4 should not be named front
and back, as methods must be named front() and back().
