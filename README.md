*This project has been created as part of the 42 curriculum by aamhamdi, kben-ham, nmaazouz.*

# ft_irc

## Description

`ft_irc` is a custom **Internet Relay Chat (IRC) server** written from scratch in C++98, without any external libraries (no Boost, no third-party socket/event libraries). The goal is to implement enough of the IRC protocol (RFC 1459 / 2812 style) for a real IRC client to connect, authenticate, join channels, exchange messages, and use channel-operator commands — exactly as it would against an official IRC server.

The server is **single-threaded and non-blocking**: a single `poll()` loop multiplexes the listening socket and every client socket, so no forking and no blocking `read`/`recv`/`write`/`send` calls are ever made outside of that loop. Partial/fragmented TCP reads are buffered per client and reassembled into complete IRC lines before being parsed.

### Implemented features

- TCP/IP server, run as `./ircserv <port> <password>`.
- Client registration: `PASS`, `NICK`, `USER`.
- Channels: `JOIN`, `PART`, `TOPIC`, `PRIVMSG` (users and channels), `QUIT`.
- Channel operators and regular users, with operator-only commands:
  - `KICK` — eject a client from a channel.
  - `INVITE` — invite a client to a channel.
  - `TOPIC` — view/change the channel topic (optionally operator-restricted via mode `t`).
  - `MODE` — channel modes `i` (invite-only), `t` (topic restricted to operators), `k` (channel key/password), `o` (grant/revoke operator), `l` (user limit).
- Standard IRC numeric replies (e.g. `433 Nickname is already in use`, `441 They aren't on that channel`, `461 Not enough parameters`, ...) so client behaviour matches a real IRC server.
- Graceful shutdown on `SIGINT` / `SIGQUIT`.

### Bonus

- **IRC bot** (`./bot <port> <password>`), a separate program that connects to the server like a regular client (using its own `poll()` loop) and responds to:
  - `help [command]` — prints usage and a short description for a known command (`PASS`, `JOIN`, `KICK`, `MODE`, `PRIVMSG`, ...).
  - `weather <city>` — fetches and replies with current weather (city, country, description, temperature, pressure, visibility) via `libcurl`.

---

## Instructions

### Compilation

```bash
make        # builds ircserv
make bot    # builds the bonus bot (requires libcurl)
make clean  # removes object files
make fclean # removes object files and binaries
make re     # fclean + all
```

Compiled with `c++ -Wall -Wextra -Werror -std=c++98` (plus `-fsanitize=address` for debug builds), with sources split across `src/` (server core) and `src/commands/` (one class per IRC command).

### Running the server

```bash
./ircserv <port> <password>
# example:
./ircserv 6667 mypassword
```

- `port`: the TCP port the server listens on.
- `password`: the connection password clients must supply via `PASS`.

### Connecting with a client

Any standard IRC client can be used (e.g. WeeChat, irssi, HexChat). Example with `irssi`:

```bash
irssi -c 127.0.0.1 -p 6667 -w mypassword -n yournick
```

Or test raw protocol behaviour directly with `nc`:

```bash
nc -C 127.0.0.1 6667
PASS mypassword
NICK alice
USER alice 0 * :Alice
JOIN #general
```

### Running the bot (bonus)

```bash
./bot <port> <password>
```

Once connected, invite/join the bot into a channel and message it directly:

```
help
help PRIVMSG
weather Paris
```

---

## Resources

- [RFC 1459 — Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812 — IRC Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
- [modern IRC client protocol docs (modern.ircdocs.horse)](https://modern.ircdocs.horse/)
- `man poll`, `man fcntl`, `man socket` — non-blocking I/O and socket setup references.
- [OpenWeatherMap API docs](https://openweathermap.org/api) — used by the bonus bot's `weather` command.

**AI usage:** AI assistance was used in a supporting role only — mainly to clarify ambiguous parts of the IRC RFCs (numeric reply formats, MODE command semantics) and to help debug specific `poll()`/non-blocking edge cases (e.g. partial reads, EOF detection on `recv`). All core design decisions — the connection/buffering model, the command class hierarchy, and the channel/mode logic — were written and understood by the team; AI-generated snippets were never copy-pasted wholesale and were always reviewed and tested before being integrated.
