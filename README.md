# Silly Little Limit Order Book Engine

### Introduction

A limit order is an order that only executes if a given price condition is met. Unlike a market order, the limit order guarantees the execution price but does not guarantee the execution.

Before meeting the price condition, it is left unexecuted and has to sit on the order book. A limit order book is a trading system used to manage these limit orders as well as match the lowest ask with the highest bid on a price-time priority basis.

This is a very basic mock limit order book with the bare functionalities needed and without much optimisations.

### Structure

The creation of this engine was loosely based on the following [article.](https://web.archive.org/web/20110219163448/http://howtohft.wordpress.com/2011/02/15/how-to-build-a-fast-limit-order-book/)

The engine is designed such that limit prices are kept within binary heaps instead whilst the orders are kept within doubly-linked-lists on a price-level basis.

This results in the following complexities for these key operations:

- Adding Bid/Ask: *O(1)*
- Cancel: *O(1)*
- Getting Best Bid/Ask: *O(1)*
- Getting Volume: *O(1)*
- Batch Order Matching & Execution: *O(nlog(n))*
