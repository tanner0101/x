#pragma once

#include "function_call.h"
#include "function_definition.h"
#include "node_type.h"
#include <iostream>
#include <string>
#include <variant>
#include <vector>

using NodeValue = std::variant<std::string, FunctionDefinition, FunctionCall>;

struct Node {
    NodeType type;
    NodeValue value;

    Node(NodeType type, NodeValue value)
        : type{type}, value{std::move(value)} {}
    Node(FunctionCall functionCall)
        : Node(NodeType::function_call, functionCall) {}
    Node(FunctionDefinition functionDefinition)
        : Node(NodeType::function_definition, functionDefinition) {}
    Node(const char* string)
        : Node(NodeType::string_literal, std::string(string)) {}
};

inline auto operator<<(std::ostream& os, Node node) -> std::ostream& {
    os << nodeTypeToString(node.type);
    switch (node.type) {
    case NodeType::identifier:
    case NodeType::string_literal:
        os << "(" << std::get<std::string>(node.value) << ")";
        break;
    case NodeType::function_definition: {
        auto functionDefinition = std::get<FunctionDefinition>(node.value);
        os << "(" << functionDefinition.name << ",";
        for (auto argument : functionDefinition.arguments) {
            os << argument;
        }
        os << ",";
        for (auto body : functionDefinition.body) {
            os << body;
        }
        os << ")";
    } break;
    case NodeType::function_call: {
        auto functionCall = std::get<FunctionCall>(node.value);
        os << "(" << functionCall.name << ",";
        for (auto argument : functionCall.arguments) {
            os << argument;
        }
        os << ")";
    } break;
    default:
        break;
    }
    return os;
}

inline auto operator==(const Node& lhs, const Node& rhs) -> bool {
    if (lhs.type != rhs.type) {
        return false;
    }

    switch (lhs.type) {
    case NodeType::identifier:
    case NodeType::string_literal:
        return std::get<std::string>(lhs.value) ==
               std::get<std::string>(rhs.value);
    case NodeType::function_definition:
        return std::get<FunctionDefinition>(lhs.value) ==
               std::get<FunctionDefinition>(rhs.value);
    case NodeType::function_call:
        return std::get<FunctionCall>(lhs.value) ==
               std::get<FunctionCall>(rhs.value);
    default:
        return false;
    }

    return false;
}