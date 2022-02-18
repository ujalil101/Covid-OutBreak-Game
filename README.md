# Covid OutBreak Game

An object oriented COVID game using C++ by creating various objects located in a two-dimensional grid that move around and behave in various ways controlled via commands inputted by the user. 

Objective: To complete all assignments without getting infected. 

Note: You lose antibodies everytime you move. When you hit 0 antibodies - GameOver! 

Tip: Collect Vaccines to increases antibodies and complete assigments! 

List of Commands with its parameters:
          
          m ID x y
          - "move": command Student ID to move to location (x, y)
          
          d ID1 ID2
          - "move towards a DoctorsOffice": command Student ID1 to start heading to DoctorsOffice ID2.
          
          c ID1 ID2
          - “move towards a Classroom”: command Student ID1 to start heading towards ClassRoom ID2.
          
          s ID
          - "stop": command Student ID to stop doing whatever it is doing
          
          v ID vaccine_amount
          - “buy vaccines”: command Student ID to buy vaccine_amount of vaccine at a DoctorsOffice.
          
          t ID assignment_amount
          - “complete assignment_amount assignments at a ClassRoom”: command Student ID to complete assignment_amount of training units at a ClassRoom.
          
          v
          - "go": advance one-time step by updating each object once.
          
          x
          - "run": advance one-time step and update each object, and repeat until either the  update function returns true for at least one of the objects, or 5          time steps have been done.
          
          q
          - "quit": terminate the program
