#include "headers/ship.h"
#include <algorithm>

// ship

const std::map<Ship::Type, std::size_t> Ship::_centerIndexes =
{
    {Type::Ship1, 0},
    {Type::Ship2, 0},
    {Type::Ship3, 1},
    {Type::Ship4, 1}
};

Ship::Ship(Type shipType): _shipType(shipType) {
    switch (shipType) {
    case Type::Ship1:
        _body = { {ShipCell(0, 0)} };
        break;
    case Type::Ship2:
        _body = { {ShipCell(0, 0)}, {ShipCell(0, 1)} };
        break;
    case Type::Ship3:
        _body = { {ShipCell(0, 0)}, {ShipCell(0, 1)},
                  {ShipCell(0, 2)} };
        break;
    case Type::Ship4:
        _body = { {ShipCell(0, 0)}, {ShipCell(0, 1)},
                  {ShipCell(0, 2)}, {ShipCell(0, 3)} };
        break;
    default:
        break;
    }
    _init_periphery();
    _bodyCondition.assign(_body.size(), true);
}

void Ship::hit_ship(const ShipCell &pos) {
    for (auto cellIndex = 0u; cellIndex < _body.size(); ++cellIndex) {
        if (_body[cellIndex] == pos) {
            _bodyCondition[cellIndex] = false;
            break;
        }
    }
}

bool Ship::is_destroyed() const {
    for (auto cellIsOK: _bodyCondition) {
        if (cellIsOK) {
            return false;
        }
    }
    return true;
}

bool Ship::_rotate() {
    if (_shipType == Ship::Type::Ship1) {
        return false;
    }
    auto centerIx = _centerIndexes.at(_shipType);
    auto &centralCell = _body[centerIx];
    // rotate body
    for (auto &cell: _body) {
        auto posX = cell.second;
        // x = x_c - (y - y_c)
        cell.second = centralCell.second + centralCell.first - cell.first;
        // y = y_c + (x - x_c)
        cell.first = centralCell.first + posX - centralCell.second;
    }
    // rotate periphery
    for (auto &cell: _shipPeriphery) {
        auto posX = cell.second;
        // x = x_c - (y - y_c)
        cell.second = centralCell.second + centralCell.first - cell.first;
        // y = y_c + (x - x_c)
        cell.first = centralCell.first + posX - centralCell.second;
    }
    // correct position if ship crosses the border
    _correct_position();
    return true;
}

void Ship::_shift_left(ShipBody &body, ShipPeriphery &periphery) {
    for (auto &cell: body) {
        --cell.second;
    }
    for (auto &cell: periphery) {
        --cell.second;
    }
}

void Ship::_shift_up(ShipBody &body, ShipPeriphery &periphery) {
    for (auto &cell: body) {
        --cell.first;
    }
    for (auto &cell: periphery) {
        --cell.first;
    }
}

void Ship::_shift_right(ShipBody &body, ShipPeriphery &periphery) {
    for (auto &cell: body) {
        ++cell.second;
    }
    for (auto &cell: periphery) {
        ++cell.second;
    }
}

void Ship::_shift_down(ShipBody &body, ShipPeriphery &periphery) {
    for (auto &cell: body) {
        ++cell.first;
    }
    for (auto &cell: periphery) {
        ++cell.first;
    }
}

void Ship::_correct_position() {
    for (auto &cell: _body) {
        while (cell.second < 0) {
            _shift_right(_body, _shipPeriphery);
        }
        while (cell.second >= Field::WIDTH) {
            _shift_left(_body, _shipPeriphery);
        }
        while (cell.first < 0) {
            _shift_down(_body, _shipPeriphery);
        }
        while (cell.first >= Field::HEIGHT) {
            _shift_up(_body, _shipPeriphery);
        }
    }
}

void Ship::_init_periphery() {
    // initially ship is horizontal and was not rotated
    auto leftCell = _body.front(); --leftCell.second;
    auto rightCell = _body.back(); ++rightCell.second;
    auto topCell = leftCell; --topCell.first;
    auto bottomCell = leftCell; ++bottomCell.first;
    // add top & bottom cells
    for (auto i = 0u; i < _body.size() + 2; ++i) {
        _shipPeriphery.push_back(topCell);
        _shipPeriphery.push_back(bottomCell);
        // shift top & bottom cells
        ++topCell.second;
        ++bottomCell.second;
    }
    // add side cells
    _shipPeriphery.push_back(leftCell);
    _shipPeriphery.push_back(rightCell);
}

bool Ship::_check_validity_of(const ShipBody &body) {
    for (auto &cell: body) {
        if (!Field::is_valid_pos(cell.first, cell.second)) {
            return false;
        }
    }
    return true;
}

void Ship::_set_body(const ShipBody &body, const ShipPeriphery &periphery) {
    _body = body;
    _shipPeriphery = periphery;
}

bool Ship::is_horizontal() const {
    return _body.front().first == _body.back().first;
}

bool Ship::is_vertical() const {
    return _body.front().second == _body.back().second;
}

Ship::Type &operator++(Ship::Type &type) {
    if (type == Ship::Type::Total) {
        type = Ship::Type::Ship1;
    }
    else {
        type = static_cast<Ship::Type>(static_cast<int>(type) + 1);
    }
    return type;
}

Ship::Type &operator--(Ship::Type &type) {
    if (type == Ship::Type::Ship1) {
        type = Ship::Type::Total;
    }
    else {
        type = static_cast<Ship::Type>(static_cast<int>(type) - 1);
    }
    return type;
}

// friends

bool operator==(const Ship &ship1, const Ship &ship2) {
    const auto &body1 = ship1.get_body();
    const auto &body2 = ship2.get_body();
    if (body1.size() != body2.size()) {
        return false;
    }
    bool isCommonCell = false;
    for (auto &shipCell1: body1) {
        isCommonCell = false;
        for (auto &shipCell2: body2) {
            if (shipCell1 == shipCell2) {
                isCommonCell = true;
                break;
            }
        }
        if (!isCommonCell) {
            return false;
        }
    }
    return true;
}
