/*
 * node.cpp
 *
 *  Created on: 22 окт. 2019 г.
 *      Author: Xiaomi
 */
#include "node.h"

using namespace std;

bool EmptyNode::Evaluate(const Date& date, const std::string& event) const
{
    return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const
{
    if (operation == Comparison::Equal) { return date == desiredDate;}
    else if (operation == Comparison::NotEqual) { return date != desiredDate;}
    else if (operation == Comparison::Less) { return date < desiredDate;}
    else if (operation == Comparison::LessOrEqual) { return date <= desiredDate;}
    else if (operation == Comparison::Greater) { return date > desiredDate;}
    else if (operation == Comparison::GreaterOrEqual) { return date >= desiredDate;}
    else return false;
}

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const
{
    if (operation == Comparison::Equal) { return event == desiredEvent;}
    else if (operation == Comparison::NotEqual) { return event != desiredEvent;}
    else if (operation == Comparison::Less) { return event < desiredEvent;}
    else if (operation == Comparison::LessOrEqual) { return event <= desiredEvent;}
    else if (operation == Comparison::Greater) { return event > desiredEvent;}
    else if (operation == Comparison::GreaterOrEqual) { return event >= desiredEvent;}
    else return false;
}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const
{
    if (operation == LogicalOperation::And) { return left->Evaluate(date, event) && right->Evaluate(date, event);}
    else if (operation == LogicalOperation::Or) { return left->Evaluate(date, event) || right->Evaluate(date, event);}
    else return false;
}
