# Description

Imagine that you are the developer of a game in which two teams of five players participate. each consists of five teams
roles: top (top), middle (mid), bottom (bot), support (sup), jungle (jungle).

### Task

Create a service that would select players for a team based on their preferences and MMR

To do this, you need to take into account the metrics:

- MMR — Matchmaking Rating (player rating obtained during the game), numerical equivalent of player skills;
- Ranked list of positions;
- Waiting time in queue.

### Assessment

The testing system evaluates:

- Fairness of the match (the chances of winning must be 50%±1%);
- Preferred positions (players rank positions in the way that is most comfortable for them);
- Search speed (players should not wait in line for too long).

### Mechanics of assessment

#### Remember that the task is a mathematical model, an approximation of the real world and your personal experience may not correspond to it

- All generated matches that you sent will be analyzed according to three parameters
- For each parameter, a rating is built for all participants in the contest, after which points are assigned
    - Fairness of the match = difference in medians between team ratings + sum of differences in mmr by role.
      - [Link to example of calculation](https://docs.google.com/spreadsheets/d/1dsavn30sd9B6QUk5k4XVJaQLprVCFzV72cCBOjWmtkM/edit?usp=sharing)
    - Preferred position = sum of player satisfaction values
      - 3 if the player is first on the list
      - 5, if second on the list
      - 8, if third on the list
      - 13, if fourth on the list
      - 21, if fifth on the list
    - Search speed = the sum of the total waiting time, taking into account pauses between epochs
      - Time is counted in seconds
      - The pauses between eras are different and you will not know their meaning

### Testing

- Your solution will be tested both on open test data in the `tests` folder, and on closed ones, which will be
  added during CI runtime
- There will be 20 tests in total, from `test_0` to `test_19`
- The maximum number of players in one test is 10_000
- The maximum number of players in one era is 10_000
- Timeout for passing tests: 10 minutes

# [Documentation](docs/docs.md)

# Interaction scheme

1) Send a GET request to `/matchmaking/users` with the parameters `test_name` and `epoch`
2) Distribute the received users among teams
3) Sending a POST request to `/matchmaking/match` with the `test_name` and `epoch` parameters and command data. In response
    you get `new_epoch`, which you now use in new requests, and `is_last_epoch`.
4) Repeat steps 1-3 until ` and `is_last_epoch`` is equal to `true`
5) Repeat until tests are completed

## Important

- It is not necessary to distribute all players into teams, but there should be <= 9 of them left
