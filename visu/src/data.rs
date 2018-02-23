use failure::Error;
use std::str::FromStr;

#[derive(Debug, Fail)]
pub enum RoomParseError {
    #[fail(display = "invalid room")] InvalidRoom,
    #[fail(display = "invalid room kind")] InvalidRoomKind,
    #[fail(display = "invalid room name")] InvalidRoomName,
    #[fail(display = "invalid coord")] InvalidCoord,
}

pub struct Link {
    room1: String,
    room2: String,
}

pub enum RoomKind {
    Start,
    End,
    Normal,
}

impl FromStr for RoomKind {
    type Err = RoomParseError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            "##start" => Ok(RoomKind::Start),
            "##end" => Ok(RoomKind::End),
            _ => bail!(RoomParseError::InvalidRoomKind),
        }
    }
}

pub struct Room {
    name: String,
    kind: RoomKind,
    pos: (usize, usize),
    full: bool,
}

impl Room {
    pub fn new(name: String, kind: RoomKind, pos: (usize, usize)) -> Room {
        Room {
            name: name,
            kind: kind,
            pos: pos,
            full: false,
        }
    }

    pub fn parse_room(s: &str) -> Result<Self, Error> {
        let mut room;
        let kind;
        let mut split = s.split('\n');
        match split.next() {
            Some(ref s) if s.starts_with("##") => {
                kind = RoomKind::from_str(s)?;
            }
            Some(ref s) => {
                return Ok(Room::from_str(s)?);
            }
            _ => bail!(RoomParseError::InvalidRoom),
        }
        room = Self::from_str(split.next().ok_or(RoomParseError::InvalidRoom)?)?;
        room.kind = kind;
        Ok(room)
    }
}

impl FromStr for Room {
    type Err = Error;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut splitted = s.split_whitespace();
        let name = splitted.next().ok_or(RoomParseError::InvalidRoomName)?;
        let x = splitted
            .next()
            .ok_or(RoomParseError::InvalidCoord)?
            .parse()
            .map_err(|_| RoomParseError::InvalidCoord)?;
        let y = splitted
            .next()
            .ok_or(RoomParseError::InvalidCoord)?
            .parse()
            .map_err(|_| RoomParseError::InvalidCoord)?;
        Ok(Room::new(name.to_string(), RoomKind::Normal, (x, y)))
    }
}
