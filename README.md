# Voting System

## Voting Management Platform

The Voting Management Platform is a role-based system designed to create, manage, and participate in polls. It supports two primary user roles:

### 1. Vote Creators (Privileged Users)

These users have elevated permissions that allow them to:
- Open new votes and define their properties.
- Specify a title, list of options, and expiration time.

### 2. General Users

All registered users in the system can:

Browse a list of active votes.

Select their preferred option(s).

Submit their vote, which the system validates to ensure the vote is still open.

A user can change his vote whenever he desires.

## Core Features
✔ Authentication & Role Management

Users must authenticate before accessing the platform. Roles determine who may create votes vs. who may only participate.

✔ Vote Creation & Management

Authorized users can define new polls with configurable options and parameters.

✔ Results Tracking

The system provides:
- Live tallies for open votes
- Final results after a vote closes
- Anonymized voting.
- Everyone voter has one vote which he can change as long as the vote is up

✔ Scalability

The platform supports multiple simultaneous polls and can handle large numbers of users voting concurrently.
