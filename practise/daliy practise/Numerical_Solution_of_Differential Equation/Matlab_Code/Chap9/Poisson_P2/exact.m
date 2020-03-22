function u=exact(coordinate, nunk)

u(1:nunk)=coordinate(1:nunk,1).*(1-coordinate(1:nunk,1)).*coordinate(1:nunk,2).*(1-coordinate(1:nunk,2));
        