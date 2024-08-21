# GET /matchmaking/users

### Input parameters

Example:

```
/matchmaking/users?test_name=test_0&epoch=00000000-0000-0000-0000-000000000000
```

- `test_name` - test name, they can be found in the `/server/tests` folder.
  - In total you need to call 20 tests, starting
    starting with `test_0` and ending with `test_19`.
- `epoch` - uuid of the epoch in the testing system. Any amount of time can pass between epochs, from a few seconds to
  several hours.
  - the first request within each test for `/matchmaking/match` must be with `epoch=00000000-0000-0000-0000-0000000000000`

### Response

Example:

```json
[
  {
    "user_id": "4877bf28-68a8-4f6c-84a8-707223e9237b",
    "mmr": 2000,
    "roles": ["top", "mid", "bot", "sup", "jungle"],
    "waitingTime": 12
  },
  ...
]
```

- `user_id` - user uuid
- `mmr` - user rating
- `roles` - list of positions sorted by priority
- `waitingTime` - waiting time in queue, in seconds

Any number of users can respond to you, but no more than 10^4

# POST matchmaking/match

### Input parameters

Example:

```/matchmaking/match?test_name=test_0&epoch=00000000-0000-0000-0000-000000000000```

```json
[
  {
    "match_id": "00000000-0000-0000-0000-000000000000",
    "teams": [
      {
        "side": "red",
        "users": [
          {
            "id": "00000000-0000-0000-0000-000000000000",
            "role": "mid"
          },
          ...
        ]
      },
      {
        "side": "blue",
        "users": [
          {
            "id": "00000000-0000-0000-0000-000000000000",
            "role": "top"
          },
          ...
        ]
      }
    ]
  },
  ...
]
```
- `match_id` - match uuid
- `teams` - team roster
  - `side` - team side `(red/blue)`
  - `users` - list of players
    - `id` - user uuid
    - `role` - player position in the game



### Response

```json
{
  "new_epoch": "00000000-0000-0000-0000-000000000000",
  "is_last_epoch": true
}
```
- `new_epoch` - uuid of the epoch to be used in the following requests
- `is_last_epoch` - a flag that shows whether this is the last era